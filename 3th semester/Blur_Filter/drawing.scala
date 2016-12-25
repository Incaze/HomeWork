/**
  * Created by Incaze on 25.12.2016.
  */

package Blur_Package

import java.io.File
import javax.imageio.ImageIO
import swing.{Panel, MainFrame, SimpleSwingApplication}
import java.awt.{Graphics2D, Dimension}
import java.awt.image.BufferedImage


class Draw_Img(img : BufferedImage) extends Panel {

  override def paintComponent(g: Graphics2D) {
    val width = img.getWidth()
    val height = img.getHeight()
    val x = g.getClipBounds.width.toFloat / width
    val y = g.getClipBounds.height.toFloat / height

    g.drawRenderedImage(img, java.awt.geom.AffineTransform.getScaleInstance(x, y))
  }
}

object before_blur extends SimpleSwingApplication {
  def top = new MainFrame {
    val img = ImageIO.read(new File("in.jpg"))
    val width = img.getWidth
    val height = img.getHeight
    contents = new Draw_Img(img) {
      preferredSize = new Dimension(width, height)
    }
  }
}

object after_blur extends SimpleSwingApplication {
  val img = ImageIO.read(new File("in.jpg"))
  val width = img.getWidth
  val height = img.getHeight
  val blur_info = info_for_blur()
  val output : BufferedImage = img
  blur_info match {
    case (radius, threads, "h") => Exe_Filter.blur_hor_par(radius, threads, output)
    case (radius, threads, "v") => Exe_Filter.blur_ver_par(radius, threads, output)
  }

  def top = new MainFrame {
    contents = new Draw_Img(output) {
      preferredSize = new Dimension(width, height)
    }
  }
}
