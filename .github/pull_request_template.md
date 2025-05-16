## Note to Developer

Pull-requests on base `rhino-*.x` branches trigger build and test actions. After the build and test actions are passed, pull-request is automatically merged into the base branch and new merge-down pull-request is created on the next `rhino-*.x` branch by major version.

To publish NuGet packages created by the build action, select the *build* action and run it manually on the base `rhino-*.x` branch.