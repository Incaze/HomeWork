object lin_com {

  type DInt = (Int, Int)
  var num1  : Array[Int] = Array.emptyIntArray
  var num2  : Array[Int] = Array.emptyIntArray
  var Arr   : Array[DInt] = Array.empty
  var threads = 1
  var num_len = 1
  var index = 0
  var last_index = 0

  private def find_power (x : Int) : Int = {
    var tmp = 1
    var res = 0
    while (tmp < x) {
      tmp *= 2
      res += 1
    }
    res
  }

  def read_num (str : String, input : Int) : Array[Int] = {
    val length = str.length
    val arr_size = scala.math.pow (2, find_power(length)).toInt
    val res: Array[Int] = new Array[Int](arr_size)
    for (i <- 0 until length) {
      res(i) = str.charAt(i).asDigit
    }
    for (i <- length until arr_size) {
      res(i) = input
    }
    res
  }

  def equal_size(arr : Array[Int], new_size : Int, input : Int) : Array[Int] = {
    val res : Array[Int] = new Array[Int](new_size)
    for (i <- arr.indices) {
      res(i) = arr(i)
    }
    val old_size = arr.length
    for (i <- old_size until new_size) {
      res(i) = input
    }
    res
  }

  def refresh_res(x : DInt, y : DInt) : DInt = (x._1 * y._1, y._1 * x._2 + y._2)

  def first_step(res : Array[DInt], period : Int, l : Int, r : Int) : Unit = {
    if (r - l + 1 == period) {
      var power = 2
      while (power <= period) {
        var i = l + power - 1
        while (i <= r) {
          res(i) = refresh_res(res(i - power / 2), res(i))
          i += power
        }
        power *= 2
      }
    }
    else {
      println(l, r)
      val new_thread = new Thread() {
        override def run() : Unit = {
          first_step(res, period, (r - l) / 2 + 1 + l, r)
        }
      }
      new_thread.start()
      first_step(res, period, l, (r - l - 1) / 2 + l)
      new_thread.join()
      res(r) = refresh_res(res((r - l - 1) / 2 + l), res(r))
    }
  }

  def start_first_step() : Array[DInt] = {
    val res : Array[DInt] = Arr
    val period = num_len / threads
    first_step(res, period, 0, num_len - 1)
    res
  }

  def second_step(res : Array[DInt], period : Int, l : Int, r : Int) : Unit = {
    if (r - l + 1 == period) {
      var power = period
      while (power >= 2) {
        var i = power + l - 1
        while (i <= r) {
          val tmp = res(i)
          res(i) = refresh_res(res(i), res(i - power / 2))
          res(i - power / 2) = tmp
          i += power
        }
        power /= 2
      }
    }
    else {
      println(l , r)
      val new_thread = new Thread() {
        override def run() : Unit = {
          second_step(res, period, (r - l) / 2 + 1 + l, r)
        }
      }
      val tmp = res(r)
      res(r) = refresh_res(res(r), res((r - l - 1) / 2 + l))
      res((r - l - 1) / 2 + l) = tmp
      new_thread.start()
      second_step(res, period, l, (r - l - 1) / 2 + l)
      new_thread.join()
    }
  }

  def start_second_step() : Array[DInt] = {

    val res : Array[DInt] = Arr
    val period = num_len / threads
    second_step(res, period, 0, num_len - 1)
    res
  }

  def solo_line(res : Array[DInt], n : Int) : Int = {
    var x = res(0)._2
    for (i <- 1 to n) {
      x = res(i)._1 * x + res(i)._2
    }
    x
  }

  def check_data(): Unit ={
    num1 = read_num(scala.io.StdIn.readLine(), 1)
    num2 = read_num(scala.io.StdIn.readLine(), 0)
    println("Enter num of threads")
    threads = scala.io.StdIn.readInt()
    println("Enter index")
    index = scala.io.StdIn.readInt()
    last_index = Math.max(num1.length, num2.length) - 1
    if (threads <= last_index + 1) {
      if (num1.length > num2.length) {
        num2 = equal_size(num2, num1.length, 0)
      } else {
        if (num1.length < num2.length) {
          num1 = equal_size(num1, num2.length, 1)
        }
      }
    }
    num_len = num1.length
    Arr = num1 zip num2
    for (i <- Arr.indices) {
      print(Arr(i))
    }
    println()
    println(solo_line(Arr, index))
  }

  def exe_line(): Unit ={
    var last_pair = (1, 0)
    if (index == last_index) {
      last_pair = Arr(last_index)
    }
    Arr = start_first_step()
    Arr(Arr.length - 1) = (1,0)
    Arr = start_second_step()
    if (index == last_index) {
      print(refresh_res(Arr(index), last_pair)._2)
    }
    else {
      print(Arr(index + 1)._2)
    }

  }

  def main(args: Array[String]): Unit = {
    check_data()
    exe_line()
  }
}
