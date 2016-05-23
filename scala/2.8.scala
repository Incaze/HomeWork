object task8 {
  def sum(l: List[Int]): Int = {
    def solve(l: List[Int], sum: Int): Int = {
      if (l.isEmpty)
        sum
      else solve(l.tail, sum + l.head)
    }
    solve(l, 0)
  }
}
