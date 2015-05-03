<?php
/*
 * Copyright 2004 - 2014
 * Matt Brubeck
 * Dominic Mazzoni
 * Richard Ash
 * Gale Andrews 
 * Vaughan Johnson
 * This file is licensed under a Creative Commons license:
 * http://creativecommons.org/licenses/by/3.0/
 */
  require_once "main.inc.php";
  require_once "../latest/versions.inc.php";
  require_once "../latest/mirror.inc.php";
  $pageId = "windows";
  $pageTitle = _("Windows");
  include "../include/header.inc.php";
?>

<h2><?=$pageTitle?></h2>

<h3><?=_("Recommended Downloads - Latest Version of Audacity")?></h3>
<ul>
  <li>
    <p>
      <?php printf(_('<a href="%s">Audacity %s installer</a> (%.1lf MB, includes help files)'), 
                    download_url($win_exe_url), win_exe_version, win_exe_size)?>
    </p>
  </li>
  <li>
    <p>
      <?php printf(_('<a href="%s">Audacity %s zip file</a> (%.1lf MB) - smaller download (without help files), also useful if you cannot run the installer because of restricted permissions'),
                    download_url($win_zip_url), win_zip_version, win_zip_size)?>
    </p>
  </li>
</ul>

<p>
  &nbsp;&nbsp;&nbsp;<a href="#sysreq"><?=_("System Requirements")?></a>
</p>

<h3 id="optional"><?=_("Optional Downloads")?></h3>
<?php
  // i18n-hint:  If this string is translated, it will appear above the list of
  // optional downloads on the "downloads/windows" page.  If there are extra
  // files available in your language, add them here.  Otherwise, do not
  // translate this string.  (Or make the translation identical to the
  // original string.)
  if (_("localized_downloads_windows") != "localized_downloads_windows") {
    echo _("localized_downloads_windows");
  }
?>
<h4><?=_("Plug-ins and Libraries")?></h4>
<ul>
  <li><p><?php printf(_('<a href="%s">LADSPA plug-ins %s installer</a> (.exe file, %.1lf MB) - Contains over 90 plug-ins.'), download_url($ladspa_url), ladspa_version, ladspa_size)?></p></li>
  <li>
    <p>
      <a href="plugins">
        <?=_("Plug-Ins")?>
      </a> - <?=_("Download additional effects and filters.")?>
    </p>
  </li>
  <li>
    <p>
      <a href="http://manual.audacityteam.org/help/manual/man/faq_installation_and_plug_ins.html#lame">
        <?=_("LAME MP3 encoder")?>
      </a> - <?=_("Allows Audacity to export MP3 files.")?>
    </p>
  </li>
  <li>
    <p>
      <a href="http://manual.audacityteam.org/o/man/faq_installation_and_plug_ins.html#ffdown">
        <?=_("FFmpeg import/export library")?>
      </a> - <?=_("Allows Audacity to import and export many additional audio formats such as AC3, AMR(NB), M4A and WMA, and to import audio from video files.")?>
    </p>
  </li>
</ul>

<h4>
  <?=_("Alternative Download Links")?>
</h4>
<ul>
  <li>
       <?php printf(_('<a href="%s">OldFoss</a> hosts the current Audacity version and all previous versions.'), "http://www.oldfoss.com/Audacity.html")?>
      </li>
      <li>
        <?php printf(_('<a href="%s">Google Code</a> hosts selected previous versions up to and including Audacity 2.0.5.'), "https://code.google.com/p/audacity/downloads/list?can=1")?>
      </li>
</ul>

<h4>
  <?=_("Nightly Builds")?>
</h4>
<ul>
  <li>
    <p>
      <?php echo _('<b>For advanced users</b>, <a href="http://wiki.audacityteam.org/index.php?title=Nightly_Builds#Windows_Binaries">nightly builds</a> are available for testing purposes.')?>
      <?php include "beta_nightly.inc.php"; ?>
    </p>
  </li>
</ul>

<?php include "windows_sys_reqs.inc.php"; ?>

<?php
  include "../include/footer.inc.php";
?>
