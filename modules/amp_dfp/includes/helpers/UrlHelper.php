<?php

class UrlHelper implements FormatHelper{
  public static function format($urls) {
    $formatted = array();
    for($i=0; $i < count($urls); $i++) {
      if(!empty($urls[$i]['rtc_error_url'])) {
        $formatted[] = (object) [
          'url' => $urls[$i]['rtc_url'],
          'errorReportingUrl' => $urls[$i]['rtc_error_url'],
        ];
      } else {
        $formatted[] = $urls[$i]['rtc_url'];
      }
    }
    return $formatted;
  }
}
