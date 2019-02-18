# rhinoinside python package
Embed Rhino in CPython

`pip install --user rhinoinside`

## Requirements:
- Rhino 7
- Windows
- 64 bit version of CPython (2.7+ or 3.3+ should work)

## How to use
```
import rhinoinside
import System
import Rhino

# for now, you need to explicitly use floating point
# numbers in Point3d constructor
pts = System.Collections.List[Rhino.Geometry.Point3d]()
pts.Add(Rhino.Geometry.Point3d(0.0,0.0,0.0))
pts.Add(Rhino.Geometry.Point3d(1.0,0.0,0.0))
pts.Add(RHino.Geometry.Point3d(1.5,2.0,0.0))

crv = Rhino.Geometry.Curve.CreateInterpolatedCurve(pts,3)
print (crv.GetLength())
```
