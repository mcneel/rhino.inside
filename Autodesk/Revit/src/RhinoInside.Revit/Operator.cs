using System;

namespace RhinoInside.Revit
{
  public static class Operator
  {
    enum CompareMethod
    {
      Nothing,
      Equals,
      StartsWith, // >
      EndsWith,   // <
      Contains,   // ?
      Wildcard,   // :
      Regex,      // ;
    }

    static CompareMethod CompareMethodFromPattern(ref string pattern, ref bool not)
    {
      if (string.IsNullOrEmpty(pattern))
        return CompareMethod.Nothing;

      switch (pattern[0])
      {
        case '~': not = !not; pattern = pattern.Substring(1); return CompareMethodFromPattern(ref pattern, ref not);
        case '>': pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.StartsWith;
        case '<': pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.EndsWith;
        case '?': pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.Contains;
        case ':': pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.Wildcard;
        case ';': pattern = pattern.Substring(1); return string.IsNullOrEmpty(pattern) ? CompareMethod.Nothing : CompareMethod.Regex;
        default: return CompareMethod.Equals;
      }
    }

    public static bool IsSymbolNameLike(this string source, string pattern)
    {
      if (pattern.Length == 0)
        return false;

      bool not = false;
      switch (CompareMethodFromPattern(ref pattern, ref not))
      {
        case CompareMethod.Nothing: return not ^ false;
        case CompareMethod.Equals: return not ^ string.Equals(source, pattern, StringComparison.OrdinalIgnoreCase);
        case CompareMethod.StartsWith: return not ^ source.StartsWith(pattern, StringComparison.OrdinalIgnoreCase);
        case CompareMethod.EndsWith: return not ^ source.EndsWith(pattern, StringComparison.OrdinalIgnoreCase);
        case CompareMethod.Contains: return not ^ (source.IndexOf(pattern, StringComparison.OrdinalIgnoreCase) >= 0);
        case CompareMethod.Wildcard: return not ^ Microsoft.VisualBasic.CompilerServices.LikeOperator.LikeString(source, pattern, Microsoft.VisualBasic.CompareMethod.Text);
        case CompareMethod.Regex: var regex = new System.Text.RegularExpressions.Regex(pattern); return not ^ regex.IsMatch(source);
      }

      return false;
    }
  }

}
