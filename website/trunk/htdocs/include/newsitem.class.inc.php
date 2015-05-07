<?php
class NewsItem {
  var $id;
  var $date;
  var $title;
  var $body;

  // Constructor.
  function NewsItem($date, $title, $body) {
    $this->date = $date;
    $this->title = $title;
    $this->body = $body;
  }

  // Returns the date, in the preferred format for the current locale.
  function dateStr() {
    // i18n-hint: Controls how dates are formatted.
    // See http://www.php.net/manual/function.strftime.php for details.
    return locale_to_unicode(strftime(_("%B %d, %Y"), $this->date));
  }
}

?>