/**
  * Created by Incaze on 25.12.2016.
  */
package Blur_Package

import java.awt.image.BufferedImage
import java.io.File
import javax.imageio.ImageIO
import org.scalameter._

object Timer_Des extends Bench.LocalTime{

  val time_config = config(
    Key.exec.minWarmupRuns -> 5,
    Key.exec.maxWarmupRuns -> 10
  ) withWarmer new Warmer.Default

  def get_time_blur_hor_par(radius: Int, threads: Int, output: BufferedImage) : Quantity[Double] ={
    val time = time_config measure{
      Exe_Filter.blur_hor_par(radius, threads, output)
    }
    time
  }

  def get_time_blur_ver_par(radius: Int, threads: Int, output: BufferedImage) : Quantity[Double] ={
    val time = time_config measure{
      Exe_Filter.blur_ver_par(radius, threads, output)
    }
    time
  }
}

object Get_Time {
  def main(args: Array[String]): Unit = {
    val img = ImageIO.read(new File("in.jpg"))
    println("Enter data for timer: ")
    val blur_info = info_for_blur()
    val output : BufferedImage = img
    blur_info match {
      case (radius, threads, "h") => println(Timer_Des.get_time_blur_hor_par(radius, threads, output))
      case (radius, threads, "v") => println(Timer_Des.get_time_blur_ver_par(radius, threads, output))
    }
  }
}
