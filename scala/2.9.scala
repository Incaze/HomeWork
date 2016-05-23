object task9 {
  def filt(list: List[Int]): List[Int] = {
    if (list.isEmpty) {
      List()
    } else if (list.head != 0) {
      list.head :: filt(list.tail)
    } else {
      filt(list.tail)
    }
  }
}
