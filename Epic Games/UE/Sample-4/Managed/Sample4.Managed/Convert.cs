using Rhino.Geometry;
using UnrealEngine.Runtime;

static class Convert
{
  #region ToRhino

  public static Point3d ToRhino(this FVector p) => new Point3d((double) p.X, (double) p.Y, (double) p.Z);

  #endregion


}

