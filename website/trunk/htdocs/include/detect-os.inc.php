<?php
/*
 * Copyright 2004 Matt Brubeck
 * This file is licensed under a Creative Commons license:
 * http://creativecommons.org/licenses/by/2.0/
 */

// Guess which download to offer, based on the user's OS.
function which_download() {
  $useragent = $_SERVER["HTTP_USER_AGENT"];
  if (preg_match("/Mac/i", $useragent))
    return "mac";
  else if (preg_match("/X11/i", $useragent))
    return "source";
  else
    return "windows";
}
?>
