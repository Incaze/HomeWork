/**
  * Created by Incaze on 25.12.2016.
  */

import org.scalameter._
import scala.annotation.tailrec
import scala.collection.GenSeq
import scala.util.Random
import math.{sqrt, pow}
object KMeans {

  type Point = (Double, Double)

  def distance(x : Point, y : Point) : Double = {
    sqrt(pow(x._1 - y._1, 2) + pow(x._2 - y._2, 2))
  }

  def generatePoints(num : Int, range : Int) : Seq[Point] = {
    val r = Random
    for {
      i <- 0 until num
    } yield (r.nextInt() + r.nextDouble(), r.nextInt() + r.nextDouble())
  }

  def initializeMeans(k : Int, points : Seq[Point]) : Seq[Point] = {
    Random.shuffle(points).take(k)
  }

  def findClosest(p : Point, means : GenSeq[Point]) : Point = {
    means.minBy(distance(p, _))
  }

  def classify(points : GenSeq[Point], means : GenSeq[Point]) : GenSeq[(Point, GenSeq[Point])] = {
    val value = (-1.0, -1.0)
    val res = means.map(c => (c, points.map(p =>
      if (findClosest(p, means) == c)
        p
      else
        value
    ).filter(_ != value)))
    res
  }

  def findAverage(oldMean : Point, points : GenSeq[Point]) : Point = {
    if (points.isEmpty)
      oldMean
    else
      (points.unzip._1.sum / points.length, points.unzip._2.sum / points.length)
  }

  def update(classified : GenSeq[(Point, GenSeq[Point])]) : GenSeq[Point] = {
    classified.map(xy => findAverage(xy._1, xy._2))
  }

  def converged(eta : Double)(oldMeans : GenSeq[Point], newMeans : GenSeq[Point]) : Boolean = {
    oldMeans.zip(newMeans).forall({
      case (old_mean, new_mean) => distance(old_mean, new_mean) < eta
    })
  }

  @tailrec
  final def kMeans(points : GenSeq[Point], means : GenSeq[Point], eta : Double) : GenSeq[Point] ={
    val next_mean = update(classify(points, means))

    if (converged(eta)(means, next_mean))
      next_mean
    else
      kMeans(points, next_mean, eta)
  }
}


object KMeans_Run{

  type Point = (Double, Double)

  def main(args: Array[String]): Unit = {

    println("Enter: ")
    println("count of points")
    val count_of_points = scala.io.StdIn.readInt()
    println("num of clusters")
    val num_of_clusters = scala.io.StdIn.readInt()
    println("eta")
    val eta = scala.io.StdIn.readDouble()

    val points = KMeans.generatePoints(num_of_clusters, count_of_points)
    val start_clusters = KMeans.initializeMeans(num_of_clusters, points)

    val time_config = config(
      Key.exec.minWarmupRuns -> 5,
      Key.exec.maxWarmupRuns -> 50
    ) withWarmer new Warmer.Default

    def SeqPoints(points: GenSeq[Point], means: GenSeq[Point]): Quantity[Double] = {
      val seq_time = time_config measure {
        KMeans.kMeans(points, means, eta)
      }
      seq_time
    }

    def ParSeqPoints(points: GenSeq[Point], means: GenSeq[Point]): Quantity[Double] = {
      val par_time = time_config measure {
        KMeans.kMeans(points.par, means.par, eta)
      }
      par_time
    }

    println("seq = ", SeqPoints(points, start_clusters))
    println("parSeq = ", ParSeqPoints(points, start_clusters))
  }
}
