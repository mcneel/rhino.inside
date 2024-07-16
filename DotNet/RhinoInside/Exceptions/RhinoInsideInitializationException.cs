using System;

namespace RhinoInside
{
  /// <summary>
  /// Rhino.Inside initialization exception
  /// </summary>
  public sealed class RhinoInsideInitializationException : Exception
  {
    public RhinoInsideInitializationException() { }
    public RhinoInsideInitializationException(string message) : base(message) { }
    public RhinoInsideInitializationException(string message, Exception innerException) : base(message, innerException) { }
  }
}
