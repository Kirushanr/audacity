<?php
/*
 * Copyright 2007-2015 by Vaughan Johnnson & Gale Andrews
 * This file is licensed under a Creative Commons license:
 * http://creativecommons.org/licenses/by/3.0/
 */
?>

<h3 id="sysreq"><?=_("System Requirements")?></h3>

<p>
  <?php printf(_('Read about Audacity on <a href="%s">Windows 8</a>, <a href="%s">7</a> and <a href="%s">Vista</a>.'), 
  "http://wiki.audacityteam.org/wiki/Windows_8_OS", "http://wiki.audacityteam.org/wiki/Windows_7_OS", "http://wiki.audacityteam.org/wiki/Windows_Vista_OS")?>
  <?=_("Windows 2000, NT, and 95 are not supported.")?>
</p>

<p>
  <?=_('The values in the <b>recommended RAM/processor speed</b> column below are for tasks like recording for an hour, or editing three 20-minute tracks simultaneously. The values in the <b>minimum RAM/processor speed</b> column will be fine for smaller/shorter tasks, especially if unnecessary programs are closed.')?>
</p>

<table class="winsysreq">
  <tr>
    <th><?=_("Windows version")?></th>
    <th><?=_("recommended RAM/<br>processor speed")?></th>
    <th><?=_("minimum RAM/<br>processor speed")?></th>
  </tr>
  <tr>
    <td>
      <ul>
         <li>Windows 8 (64-bit)</li>
         <li>Windows 7 (64-bit)</li>
       </ul>
    </td>
    <td>4 GB / 2 GHz</td>
    <td>2 GB / 1 GHz</td>
  </tr>
  <tr>
    <td>
       <ul>
          <li>Windows 8 (32-bit)</li>
          <li>Windows 7 (32-bit)  <i>(<?=_("except Windows 7 Starter")?>)</i></li>
          <li>Windows Vista (Home Premium/Business/Ultimate) (32-&nbsp;or&nbsp;64-bit)</li>
       </ul>
    </td>
    <td>4 GB / 2 GHz</td>
    <td>1 GB / 1 GHz</td>
  </tr>
  <tr>
    <td>
       <ul>
          <li>Windows 7 Starter</li>
          <li>Windows Vista (Home Basic) (32-&nbsp;or&nbsp;64-bit)</li>
       </ul>
    <td>2 GB / 1 GHz</td>
    <td>512 MB / 1 GHz</td>
  </tr>
  <tr>
    <td>
      <ul>
        <li>Windows XP (64-&nbsp;or&nbsp;32-bit)</li>
        <ul>
          <li>64-bit (x64) requires XP <a href="http://www.microsoft.com/en-us/download/details.aspx?id=17791">Service Pack 2</a>.</li>
          <li>32-bit (x86) requires XP <a href="http://support.microsoft.com/kb/322389">Service Pack 3</a>.</li>
        </ul>
      </ul>
    </td>
    <td>512 MB/1 GHz</td>
    <td>128 MB/300 MHz</td>
  </tr>
</table>

<p>&nbsp;</p>
<p>
  <?=_("Audacity works best on computers meeting more than the minimum requirements stated above. For lengthy multi-track projects, we recommend using machines of substantially higher specification than the minimums.")?>
</p>
