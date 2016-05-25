object task10 {
  def check(x: Int): Boolean = {
    x > 0
  }
  def filt(list: List[Int], check: Int => Boolean): List[Int] = {
    if (list.isEmpty) {
      List()
    } else if (check(list.head)) {
      list.head :: filt(list.tail, check)
    } else {
      filt(list.tail, check)
    }
  }
}

