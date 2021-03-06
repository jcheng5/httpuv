\docType{package}
\name{httpuv-package}
\alias{httpuv}
\alias{httpuv-package}
\title{HTTP and WebSocket server}
\description{
  HTTP and WebSocket server
}
\details{
  Allows R code to listen for and interact with HTTP and
  WebSocket clients, so you can serve web traffic directly
  out of your R process. Implementation is based on
  \href{https://github.com/joyent/libuv}{libuv} and
  \href{https://github.com/joyent/http-parser}{http-parser}.

  This is a low-level library that provides little more
  than network I/O and implementations of the HTTP and
  WebSocket protocols. For an easy way to create web
  applications, try \href{http://rstudio.com/shiny/}{Shiny}
  instead.
}
\examples{
\dontrun{
demo("echo", package="httpuv")
}
}
\author{
  Joe Cheng \email{joe@rstudio.com}
}
\seealso{
  startServer
}
\keyword{package}

