#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "PageBuilder.h"

ESP8266WebServer Server;
// root
PageElement ROOT_PAGE_ELEMENT("<a href=\"/hello\">hello</a>");
PageBuilder ROOT_PAGE("/", {ROOT_PAGE_ELEMENT});
// /hello
PageElement HELLO_PAG_ELEMENT("<a href=\"/bye\">bye</a>");
PageBuilder HELLO_PAGE("/hello", {HELLO_PAG_ELEMENT});
// /bye
PageElement BYE_PAGE_ELEMENT("Good, bye!");
PageBuilder BYE_PAGE("/bye", {BYE_PAGE_ELEMENT});
// Not found page
PageElement NOTFOUND_PAGE_ELEMENT("<p style=\"font-size:36px;color:red;\">Woops!</p><p>404 - Page not found.</p>");
PageBuilder NOTFOUND_PAGE({NOTFOUND_PAGE_ELEMENT});

void setup() {
  WiFi.softAP("esp8266ap", "12345678");
  delay(100);
  ROOT_PAGE.insert(Server);     // Add root page
  HELLO_PAGE.insert(Server);    // Add /hello page
  BYE_PAGE.insert(Server);      // Add /bye page
  NOTFOUND_PAGE.atNotFound(Server);		// Add not found page 
  Server.begin();
}

void loop() {
  Server.handleClient();
}

