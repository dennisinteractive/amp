<?php
include 'helpers/VendorHelper.php';
include 'helpers/UrlHelper.php';



class RealTimeConfiguration implements JsonSerializable {
  
  private $vendors;
  private $urls;
  private $timeout;
  
  public function __construct($vendors, $urls, $timeout) {
    $this->vendors = VendorHelper::format($vendors);
    $this->urls = UrlHelper::format($urls);
    $this->timeout = $timeout;
  }
  
  public function vendors() {
    return $this->vendors;
  }
  
  public function urls() {
    return $this->urls;
  }
  
  public function timeout() {
    return $this->timeout;
  }

  /*
  private function formatVendor($vendors) {
    $formatted = array();
    for($i= 0; $i < count($vendors); $i++) {
      $formatted = array($vendors[$i]['vendor_name'] => $this->formatMacros($vendors[$i]['macros']));
    }
    return $formatted;
  }
  */
  /*
  private function formatMacros($macros) {
    $formatted = array();
    for($i= 0; $i < count($macros); $i++) {
      $formatted = array($macros[$i]['macro'] => $macros[$i]['value']);
    }
    return $formatted;
  }
   * 
   */
/*  
  private function formatUrls($urls) {
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
*/
  public function jsonSerialize() {
    return array(
    'vendors' => $this->vendors,
    'urls' => $this->urls,
    'timeoutMillis' => $this->timeout,
    );
  }
}
