/**
  * Created by Incaze on 20.12.2016.
  */
package Blur_Package

import java.io.File
import javax.imageio.ImageIO
import java.awt.image.BufferedImage

object Exe_Filter {

  def blur_hor_par(radius: Int, threads: Int, input: BufferedImage): BufferedImage = {
    val width = input.getWidth
    val height = input.getHeight
    val period = height / threads
    val output = input
    val tasks_list = Range(0, height) by period
    val tasks = tasks_list.map(t => {
      new Thread {
        override def run(): Unit = {
          if ((t + period) > height) {
            for (i <- 0 until width;
                 j <- t until height) {
              output.setRGB(i, j, blur_filter(i, j, radius, width, height, input))
            }
          }
          else {
            for (i <- 0 until width;
                 j <- t until (t + period)) {
              output.setRGB(i, j, blur_filter(i, j, radius, width, height, input))
            }
          }
        }
      }
    })
    tasks.foreach(t => t.start)
    tasks.foreach(t => t.join)
    output
  }

  def blur_ver_par(radius: Int, threads: Int, input: BufferedImage): BufferedImage = {
    val width = input.getWidth
    val height = input.getHeight
    val period = width / threads
    val output = input
    val tasks_list = Range(0, width) by period
    val tasks = tasks_list.map(t => {
      new Thread {
        override def run(): Unit = {
          if ((t + period) > width) {
            for (i <- 0 until height;
                 j <- t until width) {
              output.setRGB(j, i, blur_filter(j, i, radius, width, height, input))
            }
          }
          else {
            for (i <- 0 until height;
                 j <- t until (t + period)) {
              output.setRGB(j, i, blur_filter(j, i, radius, width, height, input))
            }
          }
        }
      }
    })
    tasks.foreach(t => t.start)
    tasks.foreach(t => t.join)
    output
  }

  def main(args: Array[String]): Unit = {
    val img = ImageIO.read(new File("in.jpg"))

    val blur_info = info_for_blur()
    val output : BufferedImage = img
    blur_info match {
      case (radius, threads, "h") => blur_hor_par(radius, threads, output)
      case (radius, threads, "v") => blur_ver_par(radius, threads, output)
    }

    ImageIO.write(output, "jpg", new File("out.jpg"))
  }
}
