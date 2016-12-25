object Adding_Big_Integer {

  var num1  : Array[Int] = Array.emptyIntArray
  var num2  : Array[Int] = Array.emptyIntArray
  var carry : Array[Char] = Array.emptyCharArray
  var threads = 1
  var num_len = 1

  private def find_power (x : Int) : Int = {
    var tmp = 1
    var res = 0
    while (tmp < x) {
      tmp *= 2
      res += 1
    }
    res
  }

  def read_num (str : String) : Array[Int] = {
    val length = str.length
    val arr_size = scala.math.pow (2, find_power(length)).toInt
    val res: Array[Int] = new Array[Int](arr_size)
    val str_reverse = str.reverse
    for (i <- 0 until length) {
      res(i) = str_reverse.charAt(i).asDigit
    }
    for (i <- length until arr_size) {
      res(i) = 0
    }
    res
  }

  def equal_size(arr : Array[Int], new_size : Int) : Array[Int] = {
    val res : Array[Int] = new Array[Int](new_size)
    for (i <- arr.indices) {
      res(i) = arr(i)
    }
    val old_size = arr.length
    for (i <- old_size until new_size) {
      res(i) = 0
    }
    res
  }

  private def filling_arr_of_char(arr : Array[Char], l: Int, r : Int) : Array[Char] = {
    for (i <- l until r) {
      val sum = num1(i) + num2(i)
      if (sum > 9) arr(i) = 'C'
      else if (sum == 9) arr(i) = 'M'
      else arr(i) = 'N'
    }
    arr
  }

  def par_arr_of_char() : Array[Char] = {
    val res : Array[Char] = new Array[Char](num_len)
    val period = num_len / threads
    val period_sup = period until num_len by period
    val tasks = period_sup.map(x => {
        new Thread {
          override def run() : Unit = {
            filling_arr_of_char(res, x, x + period)
          }
        }
      }
    )
    tasks.foreach(x => x.start())
    filling_arr_of_char(res, 0, period)
    tasks.foreach(x => x.join())
    res
  }




  def first_step(res : Array[Char], period : Int, l : Int, r : Int) : Unit = {
    if (r - l + 1 == period) {
      var power = 2
      while (power <= period) {
        var i = l + power - 1
        while (i <= r) {
          if (res(i) == 'M') res(i) = res(i - power / 2)
          i += power
        }
        power *= 2
      }
    }
    else {
      val new_thread = new Thread() {
        override def run() : Unit = {
          first_step(res, period, (r - l) / 2 + 1 + l, r)
        }
      }
      new_thread.start()
      first_step(res, period, l, (r - l - 1) / 2 + l)
      new_thread.join()
      if (res(r) == 'M')
        res(r) =  res((r - l - 1) / 2 + l)
    }
  }

  def start_first_step() : Array[Char] = {
    val res : Array[Char] = carry
    val period = num_len / threads
    first_step(res, period, 0, num_len - 1)
    res
  }



  def second_step(res : Array[Char], period : Int, l : Int, r : Int) : Unit = {
    if (r - l + 1 == period) {
      var cur = period
      while (cur >= 2) {
        var i = cur - 1 + l
        while (i <= r) {
          val tmp = res(i)
          if (res(i) != 'M')
            res(i) = res(i - cur / 2)
          res(i - cur / 2) = tmp
          i += cur
        }
        cur /= 2
      }
    }
    else {
      val new_thread = new Thread() {
        override def run(): Unit = {
          second_step(res, period, (r - l) / 2 + l + 1, r)
        }
      }
      val tmp = res(r)
      if (res(r) != 'M')
        res(r) = res((r - l - 1) / 2 + l)
      res((r - l - 1) / 2 + l) = tmp
      new_thread.start()
      second_step(res, period, l, (r - l - 1) / 2 + l)
      new_thread.join()
    }
  }

  def start_second_step() : Array[Char] = {
    val res : Array[Char] = carry
    val period = num_len / threads
    second_step(res, period, 0, num_len - 1)
    res
  }

  def main(args: Array[String]): Unit = {
    num1 = read_num(scala.io.StdIn.readLine())
    num2 = read_num(scala.io.StdIn.readLine())
    println("Enter num of threads")
    threads = scala.io.StdIn.readInt()
    val max_threads = Math.max(num1.length, num2.length)
    if (threads <= max_threads) {
      if (num1.length > num2.length) {
        num2 = equal_size(num2, num1.length)
      } else {
        if (num1.length < num2.length) {
          num1 = equal_size(num1, num2.length)
        }
      }
      }
    num_len = num1.length
    carry = par_arr_of_char()
    carry = start_first_step()
    carry(num_len - 1) = 'M'
    carry = start_second_step()
    val res = new Array[Int](num_len + 1)
    res(num_len) = 0
    for (i <- 0 until num_len) {
      res(i) = num1(i) + num2(i)
      if (carry(i) == 'C') {
        res(i) += 1
      }
      res(i) %= 10
    }
    if (carry(num_len - 1) == 'C') {
      res(num_len) = 1
    }
    var flag = true
    for (i <- num_len to 0 by -1) {
      if (flag) {
        if (res(i) != 0) {
          flag = false
          print(res(i))
        }
      }
      else print(res(i))
    }
  }
}
