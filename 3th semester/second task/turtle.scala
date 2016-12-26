object Turtle {

  import math.{Pi, sqrt}

  type TripleD = (Double, Double, Double)

  var arr_move : Array[TripleD] = Array.empty
  var threads = 1
  var num_len = 1

  def asin(x: Double): Double =
    Math.asin(x) / Pi * 180

  def cos(x: Double): Double =
    Math.cos(x * Pi / 180)

  def sin(x: Double): Double =
    Math.sin(x * Pi / 180)

  def create_triples() : Array[TripleD] = {
    println("Enter num of threads")
    threads = scala.io.StdIn.readInt()
    println("Enter num of commands")
    num_len = scala.io.StdIn.readInt()
    if (num_len == 0) {
      println("Error: count of commands = 0")
      System.exit(1)
    }
    var tmp = 0
    if (num_len % threads != 0){
      tmp = threads - num_len % threads
    }

    val res : Array[TripleD] = new Array[TripleD](num_len + tmp)
    var i = 0
    while(i < num_len) {
      val angle = scala.io.StdIn.readLine().toDouble
      val dist = scala.io.StdIn.readLine().toDouble
      res(i) = (dist, angle, angle)
      i += 1
    }
    for (i <- num_len until (num_len + tmp)) {
      res(i) = (0.0, 0.0, 0.0)
    }
    num_len += tmp
    res
  }

  def par_xor(p : TripleD, q : TripleD) : TripleD = {
    val (a, realAlpha, alpha) = p
    val (b, realBeta,  beta)  = q

    val tmp = sqrt(a * a + b * b + 2 * a * b * cos(realBeta + alpha - realAlpha))
    if (tmp == 0) (tmp, realAlpha, (alpha + beta) % 360)
    else
      (tmp, (realAlpha + asin(b * sin(realBeta + alpha - realAlpha) / tmp)) % 360, (alpha + beta) % 360)
  }

  def res_pos(res: TripleD): (Double, Double) =
    (res._1 * cos(res._2), res._1 * sin(res._2))


  def par_start(res : Array[TripleD], period: Int, l : Int, r : Int) : Unit = {
    if (r - l + 1 == period) {
      for (i <- l + 1 to r)
        res(i) = par_xor(res(i - 1), res(i))
    }
    else {
      val new_thread = new Thread() {
        override def run() : Unit = {
          par_start(res, period, (r - l) / 2 + 1 + l, r)
        }
      }
      new_thread.start()
      par_start(res, period, l, (r - l - 1) / 2 + l)
      new_thread.join()
      res(r) = par_xor(res((r - 1 - l) / 2 + l), res(r))
    }
  }

  def lets_turtle() : Array[TripleD] = {
    val res : Array[TripleD] = arr_move
    val period = num_len / threads
    par_start(res, period, 0, num_len - 1)
    res
  }

  def main(args: Array[String]): Unit = {
    arr_move = create_triples()
    arr_move = lets_turtle()
    println(res_pos(arr_move.last))
  }
}
