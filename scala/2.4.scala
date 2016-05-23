object task4 {
  def main(k: Array[Double]): Set[Double] = {
    def quad(q: Array[Double]): Set[Double] = {
      val a: Double = q(1)
      val b: Double = q(2)
      val c: Double = q(3)
      val d: Double = b * b - 4 * a * c
      if (d >= 0) {
        Set((-b + math.sqrt(d)) / (2 * a),
          (-b - math.sqrt(d)) / (2 * a))
      }
      else {
        Set()
      }
    }
    def cube(cub: Array[Double]): Set[Double] = {
      val i: Double = cub(0)
      val a: Double = cub(1) / i
      val b: Double = cub(2) / i
      val c: Double = cub(3) / i
      val q: Double = (a * a - 3 * b) / 9
      val r: Double = (2 * a * a * a - 9 * a * b + 27 * c) / 54
      if (r * r < q * q * q) {
        val t: Double = math.acos(r / math.sqrt(q * q * q)) / 3
        Set(-2 * math.sqrt(q) * math.cos(t) - a / 3,
          -2 * math.sqrt(q) * math.cos(t - 2 * math.Pi / 3) - a / 3,
          -2 * math.sqrt(q) * math.cos(t + 2 * math.Pi / 3) - a / 3)
      }
      else {
        val m: Double = -math.signum(r) * math.pow(math.abs(r) +
          math.sqrt(r * r - q * q * q), 1 / 3)
        var n: Double = 0
        if (m != 0) {
          n = q / m
        }
        if (m == n) {
          Set((m + n) - a / 3, -m - a / 3)
        } else {
          Set((m + n) - a / 3)
        }
      }
    }
    if (k(0) == 0) {
      quad(k)
    }
    else {
      cube(k)
    }
  }
}
