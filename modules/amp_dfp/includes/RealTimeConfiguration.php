<?php

/**
 *  Implements JsonSerializable Interface
 */

class RealTimeConfiguration implements JsonSerializable {
  
  private $vendors;
  private $urls;
  private $timeout;
  
  public function __construct($vendors, $urls, $timeout) {
    $this->vendors = $this->formatVendor($vendors);
    $this->urls = $this->formatUrls($urls);
    $this->timeout = $timeout;
  }
  
  /**
   * 
   * @return $this->vendors
   */
  public function vendors() {
    return $this->vendors;
  }
  
  /**
   * 
   * @return $this->urls
   */
  public function urls() {
    return $this->urls;
  }
  
  /**
   * 
   * @return $this->timeout
   */
  public function timeout() {
    return $this->timeout;
  }
  
  /**
   * 
   * @param type $vendors
   * @return type array
   */
  private function formatVendor($vendors) {
    $formatted = array();
    for ($i= 0; $i < count($vendors); $i++) {
      $formatted[$vendors[$i]['vendor_name']] = $this->formatMacros($vendors[$i]['macros']);
    }
    
    return $formatted;
  }
  
  /**
   * 
   * @param type $macros
   * @return type array
   */
  private function formatMacros($macros) {
    $formatted = array();
    for ($i= 0; $i < count($macros); $i++) {
      $formatted[$macros[$i]['macro']] = $macros[$i]['value'] ;
    }
    return $formatted;
  }
  
  /**
   * 
   * @param type $urls
   * @return type array
   */
  private function formatUrls($urls) {
    $formatted = array();
    for ($i=0; $i < count($urls); $i++) {
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
  
  /**
   * 
   * @return type json object
   */
  public function jsonSerialize() {
    return array(
    'vendors' => $this->vendors,
    'urls' => $this->urls,
    'timeoutMillis' => $this->timeout,
    );
  }
}
