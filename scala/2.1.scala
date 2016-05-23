object pascal {
    def main(args: Array[String]) {
        def solve(x: Int, y: Int): Int = {
            if (x > y) 0 
            else if (x == y || x == 0) 1
            else solve(x, y - 1) + solve(x - 1, y - 1)
        }
        println(solve(2, 8))
    }
}
