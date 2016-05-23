object task10 {
  def check(x: Int): Boolean = {
    if (x > 0) {
      true
    }
    else {
      false
    }
  }
  def filt(list: List[Int]): List[Int] = {
    if (list.isEmpty) {
      List()
    } else if (check(list.head)) {
      list.head :: filt(list.tail)
    } else {
      filt(list.tail)
    }
  }
}

