object task7 {
  def len(l: List[Int]): Int = {
    def solve(l: List[Int], res: Int): Int = {
      if (l.isEmpty)
        res
      else solve(l.tail, res + 1)
    }
    solve(l, 0)
  }
}
