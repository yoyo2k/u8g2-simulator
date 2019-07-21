
void progressBar(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t percent)
{
    // can't draw it smaller than 10x8
    height = height < 8 ? 8 : height;
    width = width < 10 ? 10 : width;

    // draw percentage
    u8g2.setFont(u8g2_font_5x8);
    u8g2.drawStr(x + width / 2 - 5 * 1, y - 1, String(percent) + String("%"))

    // draw it
    u8g2.drawRFrame(x, y, width, height, 4);
    u8g2.drawBox(x + 2, y + 2, (width - 4) * (percent / 100), height - 4);
}

void button(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t width, String str, bool clicked)
{
    if (clicked) {
        u8g2.setDrawColor(1);
        u8g2.drawRBox(x, y+1, width,  u8g2.getMaxCharHeight() + 4, 2);
        u8g2.setDrawColor(0);
        u8g2.setFont(u8g2_font_courB08);
        u8g2.drawStr(x + (width / 2) - ((String(str).length() * (u8g2.getMaxCharWidth())) / 2), y + u8g2.getMaxCharHeight()+3, str);
    } else {
        u8g2.setDrawColor(1);
        u8g2.drawRFrame(x, y, width,  u8g2.getMaxCharHeight() + 6, 4);
        u8g2.setFont(u8g2_font_courB08);
        u8g2.drawStr(x + (width / 2) - ((String(str).length() * (u8g2.getMaxCharWidth())) / 2), y + u8g2.getMaxCharHeight()+2, str);      
    }
}

void gauge(U8G2 u8g2, uint8_t x, uint8_t y, uint8_t r, uint8_t percent) {
    uint8_t rx = x + r;
    uint8_t ry = y;

    uint8_t px = rx + (r-2) * cos(2 * PI * (percent/2.0 + 50)/100);
    uint8_t py = ry + (r-2) * sin(2 * PI * (percent/2.0 + 50)/100);

    u8g2.drawLine(rx,ry,px,py);

    u8g2.drawCircle(rx, y, r, U8G2_DRAW_UPPER_LEFT);
    u8g2.drawCircle(rx, y, r, U8G2_DRAW_UPPER_RIGHT);
}

void draw(U8G2 u8g2)
{
    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_5x8);
    u8g2.drawStr(2, 8,String("Progressbar:"))

    progressBar(u8g2, 2, 18, u8g2.getDisplayWidth() / 2, 10, counter % 101);

    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_5x8);
    u8g2.drawStr(2, 38,String("Button:"))

    button(u8g2, 2, 40, 48,counter % 2 ? "Clicked" : "Default", counter % 2 ? true: false);

    u8g2.setDrawColor(1);
    u8g2.setFont(u8g2_font_5x8);
    u8g2.drawStr(70, 38,String("Gauge:"))
    gauge(u8g2, 70,60,12, counter % 100);
    gauge(u8g2, 100,60,12, (counter+60) % 100);
}