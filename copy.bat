@echo off
IF "%~1"=="release" (
    robocopy "./resources" "./build" /xn /xo /ns /nc /njs /nfl /ndl /s /e
) ELSE IF "%~1"=="debug" (
    robocopy "./resources" "./build/resources" /xo /xn /ns /nc /njs /nfl /ndl /s /e
) ELSE (
    echo.
    echo build.bat usage:
    echo build release - builds the release version (the deliverable)
    echo build debug - builds the debug version (the internal test)
)
robocopy "./win-DLLs" "./build" /xn /xo /ns /nc /njs /nfl /ndl /s /e
