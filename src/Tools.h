#include <Arduino.h>

// RGBtoHEX
String RGBtoHEX(int r, int g, int b)
{
    String rs = String(r, HEX);
    String gs = String(g, HEX);
    String bs = String(b, HEX);

    if (rs.length() == 1)
        rs = "0" + rs;
    if (gs.length() == 1)
        gs = "0" + gs;
    if (bs.length() == 1)
        bs = "0" + bs;

    return rs + gs + bs;
}

// HEXtoRGB
void HEXtoRGB(String hex, uint8_t &r, uint8_t &g, uint8_t &b)
{
    // Remove # if it exists
    hex.replace("#", "");
    // trim to 6 characters
    hex = hex.substring(0, 6);
    // check of the string is a valid hex color
    // regex: ^#?([a-f0-9]{6}|[a-f0-9]{3})$
    if (hex.length() == 6)
    {
        r = strtol(hex.substring(0, 2).c_str(), nullptr, 16);
        g = strtol(hex.substring(2, 4).c_str(), nullptr, 16);
        b = strtol(hex.substring(4, 6).c_str(), nullptr, 16);
    }
    else
    {
        r = 0;
        g = 0;
        b = 0;
    }
}