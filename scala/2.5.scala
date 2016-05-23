object task5 {
  def reverse(l : List[Int]) : List[Int] = {
    def revList(l : List[Int], res : List[Int]) : List[Int] = {
      if (l.isEmpty)
        res
      else revList(l.tail, l.head :: res)
    }
    revList(l, List())
  }
}
