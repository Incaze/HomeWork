/**
  * Created by Incaze on 25.12.2016.
  */

import org.scalatest.FunSuite

class Unit_Test extends FunSuite {

  type Point = (Double, Double)

  test("Distance Test") {
    val a = (6.0, 10.0)
    val b = (7.0, 10.0)

    assert(KMeans.distance(a, b) == 1.0)
  }

  test("Find Closest Cluster") {
    val point        = (10.0, 10.0)
    val fst_cluster  = (0.0, 0.0)
    val snd_cluster  = (40.0, 40.0)
    val means = Seq[Point](fst_cluster, snd_cluster)

    assert(KMeans.findClosest(point, means) == fst_cluster)
  }

  test("Find Center of Cluster") {
    val fst_pnt  = (50.0, 50.0)
    val snd_pnt  = (0.0, 0.0)
    val thd_pnt  = (100.0, 100.0)
    val points = Seq[Point](fst_pnt, snd_pnt, thd_pnt)

    assert(KMeans.findAverage(null, points) == fst_pnt)
  }

  test("KMeans") {
    val fst_pnt = (0.0, 0.0)
    val snd_pnt = (100.0, 100.0)
    val thd_pnt = (10.0, 10.0)
    val num_of_clusters = 2
    val points = Seq[Point](fst_pnt, snd_pnt, thd_pnt)
    val start_clusters = KMeans.initializeMeans(num_of_clusters, points)
    val eta = 5.0

    assert(KMeans.kMeans(points, start_clusters, eta) equals Seq[Point]((5.0, 5.0), (100.0, 100.0)))
  }
}
