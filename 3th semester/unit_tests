/**
  * Created by Incaze on 25.12.2016.
  */

package Blur_Package

import java.awt.image.BufferedImage
import org.scalatest.FunSuite

class Unit_Tests extends FunSuite{

  test("RGB") {
    val Red = 0x11
    val Green = 0x22
    val Blue = 0x33
    val Check = 0x112233
    assert(red(Check) == Red)
    assert(green(Check) == Green)
    assert(blue(Check) == Blue)
  }

  test("Total color") {
    val Red = 0x11
    val Green = 0x22
    val Blue = 0x33
    val Check = 0x112233
    assert(total_color(Red, Green, Blue) == Check)
  }

  test("Blur Filter") {
    val img = new BufferedImage(2,2, BufferedImage.TYPE_INT_RGB)
    img.setRGB(0,0,0xFFFF00)
    img.setRGB(0,1,0xFFFF00)
    img.setRGB(1,0,0xFFFF00)
    img.setRGB(1,1,0xFFFF00)
    assert(blur_filter(1, 1, 1, 1, 1, img) == 0xFFFF00)
  }

}
