object bracket {
    def balance(str: List[Char]): Boolean = {
        def solve(str: List[Char], op: Int): Boolean = {
            if (str.isEmpty) op == 0
            else if (str.head == '('){
                solve(str.tail, op + 1)
            }
            else if (str.head == ')'){
                if (op != 0) solve(str.tail, op - 1)
                else false  
            }
            else solve(str.tail, op)
        }
        solve(str, 0)
    }
    def main(args: Array[String]) {
    println(balance("(())()((()(()))".toList))
  }
}
