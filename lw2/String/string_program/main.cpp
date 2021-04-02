#include <iostream>
#include <string>

#include "html_decode.h"

// HTML Decode 
int main()
{
    HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s");

    return 0;
}