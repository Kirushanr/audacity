<?php
  function download_url($filename) {
    $url_array =
      array("http://www.fosshub.com/Audacity.html/"
            // Comment out SF, but keep it here to make it easy to restore, if needed. 
            // , "http://sourceforge.net/projects/audacity/files/"
            );
    $url = $url_array[mt_rand() % count($url_array)];
    return $url . $filename;
  }
?>
