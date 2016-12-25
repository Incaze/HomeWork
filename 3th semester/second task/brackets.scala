object Brackets {

  var brackets_pair : Array[(Int, Int)] = Array.empty
  var threads = 1
  var num_len = 1

  def filling_arr_of_int(str : String, arr : Array[(Int, Int)], l : Int, r : Int) : Array[(Int, Int)] = {
    for (i <- l to r) {
      if (str(i) == '(')
        arr(i) = (1,0)
      else arr(i) = (0,1)
    }
    arr
  }

  def create_bracket_pairs() : Array[(Int, Int)] = {
    val str = scala.io.StdIn.readLine()
    val res : Array[(Int, Int)] = new Array[(Int, Int)](str.length)
    println("Enter num of threads")
    threads = scala.io.StdIn.readInt()
    val max_threads = str.length
    if (threads > max_threads) {
      println("Input num of threads > max threads")
      System.exit(0)
    }
    val period = str.length / threads
    val period_sup = period until str.length by period
    val tasks = period_sup.map(x => {
      new Thread {
        override def run() : Unit = {
          filling_arr_of_int(str, res, x, x + period - 1)
        }
      }
    }
    )
    tasks.foreach(x => x.start())
    filling_arr_of_int(str, res, 0, period - 1)
    tasks.foreach(x => x.join())
    res
  }

  def brackets_check(res : Array[(Int, Int)], period : Int, l : Int, r : Int) : Array[(Int, Int)] = {
    if (r - l + 1 == period) {
      for (i <- l + 1 to r) {
        val tmp = Math.min(res(i - 1)._1, res(i)._2)
        res(i) = (res(i - 1)._1 + res(i)._1 - tmp,
                  res(i - 1)._2 + res(i)._2 - tmp)
      }
    }
    else {
      val new_thread = new Thread() {
        override def run() : Unit = {
          brackets_check(res, period, (r - l) / 2 + 1 + l, r)
        }
      }
      new_thread.start()
      brackets_check(res, period, l, (r - l - 1) / 2 + l)
      new_thread.join()
      val k = (r - l - 1) / 2 + l
      val tmp = Math.min(res(k)._1, res(r)._2)
      res(r) = (res(k)._1 + res(r)._1 - tmp,
                res(k)._2 + res(r)._2 - tmp)
    }
    res
  }

  def main(args: Array[String]): Unit = {
    brackets_pair = create_bracket_pairs()
    num_len = brackets_pair.length
    val period = num_len / threads
    brackets_pair = brackets_check(brackets_pair, period, 0, num_len - 1)
    if (brackets_pair(num_len - 1) == (0,0))
      println("Correct")
    else println("Not correct")
  }
}
