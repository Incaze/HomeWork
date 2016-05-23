object task6 {
  def toEnd(l: List[Int], elem: Int): List[Int] = {
    def reverse(l: List[Int]): List[Int] = {
      def revList(l: List[Int], res: List[Int]): List[Int] = {
        if (l.isEmpty)
          res
        else revList(l.tail, l.head :: res)
      }
      revList(l, List())
    }
    reverse(elem :: reverse(l))
  }
}
