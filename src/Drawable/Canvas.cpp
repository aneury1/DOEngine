#include "Geometric.h"
#include "Application.h"
#include "Canvas.h"
#include "TTFText.h"

#if 0 

void log(const std::string_view message,
         const std::source_location location =
               std::source_location::current())
{
    std::clog << "file: "
              << location.file_name() << '('
              << location.line() << ':'
              << location.column() << ") `"
              << location.function_name() << "`: "
              << message << '\n';
}
 
void drawPixel(SDL_Renderer* renderer, int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void drawFilledOval(SDL_Renderer* renderer, int x, int y, int radiusX, int radiusY) {
    int a = radiusX;
    int b = radiusY;

    int x0 = 0;
    int y0 = b;
    int d = b * b - a * a * b + a * a / 4;

    while (b * b * (x0 + 1) < a * a * (y0 - 0.5)) {
        if (d < 0) {
            d += b * b * (2 * x0 + 3);
        } else {
            d += b * b * (2 * x0 + 3) + a * a * (-2 * y0 + 2);
            y0--;
        }
        x0++;
        SDL_RenderDrawLine(renderer, x + x0, y + y0, x - x0, y + y0);
        SDL_RenderDrawLine(renderer, x + x0, y - y0, x - x0, y - y0);
    }

    d = b * b * (x0 + 0.5) * (x0 + 0.5) + a * a * (y0 - 1) * (y0 - 1) - a * a * b * b;

    while (y0 >= 0) {
        if (d < 0) {
            d += b * b * (2 * x0 + 2) + a * a * (-2 * y0 + 3);
            x0++;
        } else {
            d += a * a * (-2 * y0 + 3);
        }
        y0--;
        SDL_RenderDrawLine(renderer, x + x0, y + y0, x - x0, y + y0);
        SDL_RenderDrawLine(renderer, x + x0, y - y0, x - x0, y - y0);
    }
}

void drawRoundedRectangle(SDL_Renderer* renderer, int x, int y, int w, int h, int radius) {
    
}

void drawOval(SDL_Renderer* renderer, int x, int y, int radiusX, int radiusY) {
     int a = radiusX;
    int b = radiusY;

    int x0 = 0;
    int y0 = b;
    int d = b * b - a * a * b + a * a / 4;

    while (b * b * (x0 + 1) < a * a * (y0 - 0.5)) {
        if (d < 0) {
            d += b * b * (2 * x0 + 3);
        } else {
            d += b * b * (2 * x0 + 3) + a * a * (-2 * y0 + 2);
            y0--;
        }
        x0++;
        SDL_RenderDrawPoint(renderer, x + x0, y + y0);
        SDL_RenderDrawPoint(renderer, x - x0, y + y0);
        SDL_RenderDrawPoint(renderer, x + x0, y - y0);
        SDL_RenderDrawPoint(renderer, x - x0, y - y0);
    }

    d = b * b * (x0 + 0.5) * (x0 + 0.5) + a * a * (y0 - 1) * (y0 - 1) - a * a * b * b;

    while (y0 >= 0) {
        if (d < 0) {
            d += b * b * (2 * x0 + 2) + a * a * (-2 * y0 + 3);
            x0++;
        } else {
            d += a * a * (-2 * y0 + 3);
        }
        y0--;
        SDL_RenderDrawPoint(renderer, x + x0, y + y0);
        SDL_RenderDrawPoint(renderer, x - x0, y + y0);
        SDL_RenderDrawPoint(renderer, x + x0, y - y0);
        SDL_RenderDrawPoint(renderer, x - x0, y - y0);
    }
  
   
    int a = radiusX;
    int b = radiusY;
    int a2 = a * a;
    int b2 = b * b;
    int twoA2 = 2 * a2;
    int twoB2 = 2 * b2;
    int x = 0;
    int y = b;
    int changeX = b2 * (1 - 2 * b);
    int changeY = a2;
    int ellipseError = 0;
    int stoppingX = b2 / sqrt(b2 + a2);
    int stoppingY = 0;

    while (stoppingX >= stoppingY) {
        // Draw points in all octants
        drawPixel(renderer, x0 + x, y0 + y);
        drawPixel(renderer, x0 - x, y0 + y);
        drawPixel(renderer, x0 + x, y0 - y);
        drawPixel(renderer, x0 - x, y0 - y);

        stoppingY++;
        y--;
        ellipseError += changeY;
        changeY += twoA2;

        if (2 * ellipseError + changeX > 0) {
            x++;
            ellipseError += changeX;
            changeX += twoB2;
        }
    }

    x = a;
    y = 0;
    changeX = b2;
    changeY = a2 * (1 - 2 * a);
    ellipseError = 0;
    stoppingX = 0;
    stoppingY = a2 / sqrt(b2 + a2);

    while (stoppingX <= stoppingY) {
        // Draw points in all octants
        drawPixel(renderer, x0 + x, y0 + y);
        drawPixel(renderer, x0 - x, y0 + y);
        drawPixel(renderer, x0 + x, y0 - y);
        drawPixel(renderer, x0 - x, y0 - y);

        stoppingX++;
        x--;
        ellipseError += changeX;
        changeX += twoB2;

        if (2 * ellipseError + changeY > 0) {
            y++;
            ellipseError += changeY;
            changeY += twoA2;
        }
    }
 
}


namespace {
    SDL_Color _color={0,0,0,255};
    Rect   _offset={0,0,800,800};
}
void begin(Window *window){
    
}
void end(Window *window){
    
}

void setCurrentCanvasPosition(int x, int y){
   _offset.x = x;
   _offset.y = y;
}
void setCurrentCanvasSize(int w, int h){
    _offset.w = w;
    _offset.h = h;
}

void fillStyle(SDL_Color color){
    _color.r = color.r;
    _color.g = color.g;
    _color.b = color.b;
    _color.a = color.a;
}
void fillRect(Window *window, int x, int y, int w, int h){
    Rect  rect{_offset.x + x, _offset.y+ y,w,h};
    DrawFillRect(rect,_color,window);
}

void DrawRect(Window *window, int x, int y, int w, int h){
    Rect  rect{_offset.x + x, _offset.y+ y,_offset.w,_offset.h};
    DrawRect(rect,_color,window);
}
void arc(Window *window, int x, int y, int radius, double startAngle, double endAngle ) {
    
  
    const int NUM_SEGMENTS = 100; // Number of line segments to approximate the arc
    SDL_SetRenderDrawColor(Application::getApplication()->getRender(), _color.r, _color.g, _color.b, _color.a);
 
    for (int i = 0; i <= NUM_SEGMENTS; ++i) 
    {
        double angle = startAngle + (endAngle - startAngle) * i / NUM_SEGMENTS;
        int x1 = x + static_cast<int>(radius * cos(angle));
        int y1 = y + static_cast<int>(radius * sin(angle));
        
          SDL_RenderDrawPoint(Application::getApplication()->getRender(), _offset.x+x1, _offset.y+ y1);
 
    }
 
}

void DrawPoint(const Point &point, const Color& color){
   /// SDL_SetRenderDrawColor(Application::getApplication()->getRender(), color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), point.x, point.y);
}
void DrawLine(const Point& p1, const Point& p2, const Color &color, Window *window){
     SDL_RenderDrawLine(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), p1.x, p1.y, p2.x, p2.y);
}

void DrawRect(const Rect &rect, const Color& color, Window *window){
   SDL_RenderDrawRect(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), &rect);
}
void DrawFillRect(const Rect &rect, const Color& color, Window *window){
  SDL_RenderFillRect(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), &rect);
}


void FillCircle(int x, int y, int radius, const Color& color)
	{
		int x0 = 0;
		int y0 = radius;
		int d = 3 - 2 * radius;
		if (!radius) return;

		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				DrawPoint({i, ny}, color, window);
		};

		while (y0 >= x0)
		{
			// Modified to draw scan-lines instead of edges
			drawline(x - x0, x + x0, y - y0);
			drawline(x - y0, x + y0, y - x0);
			drawline(x - x0, x + x0, y + y0);
			drawline(x - y0, x + y0, y + x0);
			if (d < 0) d += 4 * x0++ + 6;
			else d += 4 * (x0++ - y0--) + 10;
		}
	}


void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, const Color& p, Window *window)
{
		DrawLine({x1, y1}, {x2, y2}, p, window);
		DrawLine({x2, y2}, {x3, y3}, p, window);
		DrawLine({x3, y3}, {x1, y1}, p, window);
}

 


void DrawRect(SDL_Renderer *render, Rect  rect){
    SDL_RenderDrawRect(render, &rect);
}

void DrawRect(Window *window, Rect  rect){
    SDL_RenderDrawRect(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), &rect);
}

void DrawSinglePoint(const Rect &rect, const Color& color){
   SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), color.r, color.g, color.b, color.a); 
   SDL_RenderDrawPoint(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), rect.x, rect.y);
}
void DrawNotFillRect(const Rect &rect, const Color& color){
   SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), color.r, color.g, color.b, color.a);
   SDL_RenderDrawRect(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), &rect);
}
void DrawFillRect(const Rect &rect, const Color& color){
  SDL_SetRenderDrawColor(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()), &rect);
}

#if 0 
// Create a gradient color between two colors at a specific position
SDL_Color GradientColor(SDL_Color startColor, SDL_Color endColor, float position) {
    SDL_Color result;
    result.r = startColor.r + (endColor.r - startColor.r) * position;
    result.g = startColor.g + (endColor.g - startColor.g) * position;
    result.b = startColor.b + (endColor.b - startColor.b) * position;
    result.a = startColor.a + (endColor.a - startColor.a) * position;
    return result;
}

// Draw a horizontal line on the renderer with a gradient
void DrawGradientHorizontalLine(SDL_Renderer* renderer, int x, int y, int width, SDL_Color startColor, SDL_Color endColor) {
    for (int i = 0; i < width; i++) {
        float position = (float)i / (float)(width - 1); // Normalized position for the gradient
        SDL_Color color = GradientColor(startColor, endColor, position);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawPoint(renderer, x + i, y);
    }
}

// Draw a gradient-filled rectangle on the renderer
void DrawGradientRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color startColor, SDL_Color endColor) {
    for (int i = 0; i < height; i++) {
        float position = (float)i / (float)(height - 1); // Normalized position for the gradient
        SDL_Color color = GradientColor(startColor, endColor, position);
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer, x, y + i, x + width - 1, y + i);
    }
}

// Draw a gradient-filled circle on the renderer
void DrawGradientCircle(SDL_Renderer* renderer, int centerX, int centerY, int radius, SDL_Color startColor, SDL_Color endColor) {
    for (int y = centerY - radius; y <= centerY + radius; y++) {
        for (int x = centerX - radius; x <= centerX + radius; x++) {
            float distance = sqrtf((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));
            if (distance <= radius) {
                float position = distance / radius; // Normalized position for the gradient
                SDL_Color color = GradientColor(startColor, endColor, position);
                SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}
 

void FillCircle(int x, int y, int radius, const Color& color)
	{
		int x0 = 0;
		int y0 = radius;
		int d = 3 - 2 * radius;
		if (!radius) return;

		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				DrawSinglePoint({i, ny}, color);
		};

		while (y0 >= x0)
		{
			// Modified to draw scan-lines instead of edges
			drawline(x - x0, x + x0, y - y0);
			drawline(x - y0, x + y0, y - x0);
			drawline(x - x0, x + x0, y + y0);
			drawline(x - y0, x + y0, y + x0);
			if (d < 0) d += 4 * x0++ + 6;
			else d += 4 * (x0++ - y0--) + 10;
		}
	}


void CanvasCircleCommand::Draw()
{
 FillCircle(where.x, where.y,  radius, color);
}


void CanvasRectCommand::Draw()
{
  // SDL_Log("Render Rect [%ld, %ld, %ld %ld](%02x %02x %02x %02x)", offset.x, offset.y, offset.w, offset.h, color.r, color.g, color.b, color.a);
   ////  SDL_Log("Canvas Draw[%ld, %ld, %ld, %ld]",  offset.x, offset.y,  offset.w, offset.h);
 
   if(filled)
       DrawFillRect(offset, color);
    else
       DrawNotFillRect(offset, color );
}


void CanvasPointDrawCommand::Draw()
{
   DrawSinglePoint(offset, color);
}


void CanvasTextDrawerCommand::Draw(){
 
   TTFText::get()->setColor(color);
   TTFText::get()->DrawText(this->text.c_str(), where.x, where.y, static_cast<SDL_Renderer*>(Application::getApplication()->getRender()->getNativeRenderer()));  
}


Canvas* Canvas::setCanvasBackgroundColor(SDL_Color color)
{ 
    _bg.r = color.r;
    _bg.g = color.g;
    _bg.b = color.b;
    _bg.a = color.a;
    return this;
}

const SDL_Color Canvas::black={0,0,0,255};

Canvas::Canvas()
{ 
    setCanvasBackgroundColor({255,255,255,255});
    fillColor({0,0,0,255});
    setRect({0,0,Application::getApplication()->getW(), Application::getApplication()->getH()});
}  

Canvas* Canvas::fillColor(SDL_Color color)
{
    _filler.r = color.r;
    _filler.g = color.g;
    _filler.b = color.b;
    _filler.a = color.a;
    return this;
}
   
Canvas* Canvas::setRect(Rect  rect)
{
   _offset.x = rect.x;
   _offset.y = rect.y;
   _offset.w = rect.w;
   _offset.h = rect.h;
   return this;
}
Canvas* Canvas::DrawPoint(int x, int y)
{
    CanvasPointDrawCommand* rect = new CanvasPointDrawCommand();
    rect->offset.x =  this->_offset.x + x;
    rect->offset.y =  this->_offset.y + y;
    rect->offset.w =  1;
    rect->offset.h =  1; 
    rect->color.r =   _filler.r;
    rect->color.g =   _filler.g;
    rect->color.b =  _filler.b;
    rect->color.a =  _filler.a;

    this->commands_to_draw.push_back(rect);
    return this;
}

 Canvas* Canvas::FillCircle(int x, int y, double rsize)
 {
    CanvasCircleCommand *cmd = new CanvasCircleCommand();
    cmd->color = _filler;
    cmd->radius = rsize;
    cmd->where.x = x;
    cmd->where.y = y;
        this->commands_to_draw.push_back(cmd);
    return this;
 }

Canvas* Canvas::DrawRect(int x, int y, int w, int h, bool filled)
{
    CanvasRectCommand* rect = new CanvasRectCommand();
    rect->offset.x =  this->_offset.x + x;
    rect->offset.y =  this->_offset.y + y;
    rect->offset.w =  w;
    rect->offset.h =  h;
    rect->color.r =   _filler.r;
    rect->color.g =   _filler.g;
    rect->color.b =  _filler.b;
    rect->color.a =  _filler.a;
    rect->filled = filled;

    this->commands_to_draw.push_back(rect);

    return this;
}


Canvas* Canvas::FillText(const char *str, int x, int y)
{
    CanvasTextDrawerCommand *scanvas = new CanvasTextDrawerCommand();
    scanvas->where.x = x;
    scanvas->where.y = y;
    scanvas->color.r = _filler.r;
    scanvas->color.g = _filler.g;
    scanvas->color.b = _filler.b;
    scanvas->color.a = _filler.a;
    scanvas->text = str;
    this->commands_to_draw.push_back(scanvas);
    
    return this;
}




 Canvas* Canvas::update()
 {
 
    setCanvasBackgroundColor(_bg);
 
    ::DrawFillRect(_offset, _bg);
   
    for(auto it : commands_to_draw)
    {  
         it->Draw();
    }
   return this;
 }

Canvas* Canvas::clearCanvas(){
    ///for(auto it : commands_to_draw)
    commands_to_draw.erase(commands_to_draw.begin(), commands_to_draw.end());
    commands_to_draw.clear();
    return this;
}

#endif
#endif