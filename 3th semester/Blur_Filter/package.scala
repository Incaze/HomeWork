/**
  * Created by Incaze on 19.12.2016.
  */

import java.awt.image.BufferedImage

package object Blur_Package {

  def red(pixel : Int)     : Int = pixel >>> 0 & 0xff
  def green(pixel : Int)   : Int = pixel >>> 8 & 0xff
  def blue(pixel : Int)    : Int = pixel >>> 16 & 0xff

  def total_color(Red: Int, Green: Int, Blue: Int): Int = {
    Red | (Green << 8) | (Blue << 16)
  }

  def blur_filter(x : Int, y : Int, rad : Int, w : Int, h : Int, arr : BufferedImage) : Int = {

    var Red = 0
    var Green = 0
    var Blue = 0
    var Red_sum = 0
    var Green_sum = 0
    var Blue_sum = 0
    var total = 0

    for (i <- (x - rad) until (x + rad))
      for (j <- (y - rad) until (y + rad)){
        if ((i >= 0) && (i < w) && (j >= 0) && (j < h)) {
          Red = red(arr.getRGB(i, j))
          Green = green(arr.getRGB(i, j))
          Blue = blue(arr.getRGB(i, j))

          Red_sum += Red
          Green_sum += Green
          Blue_sum += Blue
          total += 1
        }
      }
    Red_sum /= total
    Green_sum /= total
    Blue_sum /= total

    total_color(Red_sum, Green_sum, Blue_sum)
  }

  def info_for_blur() : (Int, Int, String) ={
    println("Enter number of threads")
    val threads   = scala.io.StdIn.readInt()
    println("Enter radius of Blur")
    val radius    = scala.io.StdIn.readInt()
    println("Choose h or v")
    val blur_type = scala.io.StdIn.readLine()
    (radius, threads, blur_type)
  }

}
