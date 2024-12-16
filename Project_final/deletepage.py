from function import pygame, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE, BLACK, RED, GRAY, LIGHT_RED
from object import Button, InputBox

class DeletePage(pygame.sprite.Sprite):
    # class variable
    WIDTH = 800
    HEIGHT = 300

    inputBoxHieght = 40
    inputBoxTextSize = 25
    inputBoxBackgroundColor = WHITE

    def __init__(self):
        super().__init__()
        self.is_open = False    # page status

        self.background = pygame.Surface((DeletePage.WIDTH, DeletePage.HEIGHT))
        self.background.fill(GRAY)
        self.rect = self.background.get_rect()
        self.rect.center = (WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2) # set the center of the page to the center of the window
        self.x = self.rect.topleft[0]
        self.y = self.rect.topleft[1]
        
        # buttons
        self.close = Button(self.x + DeletePage.WIDTH - 40, self.y + 0, 40, 40, "x", RED, None, 40, WHITE)
        self.ensure = Button(self.rect.right - 200 - 50, self.rect.bottom - 50 - 50, 200, 50, "DELETE", RED, None, 30, WHITE)
        # input boxes
        self.name = InputBox(self.x + 50, self.y + 50, 200, DeletePage.inputBoxHieght, DeletePage.inputBoxBackgroundColor, DeletePage.inputBoxTextSize, BLACK, "name")      # criminal basic information

        self.year =     InputBox(self.x + 50, self.y + 200, 80, DeletePage.inputBoxHieght, DeletePage.inputBoxBackgroundColor, DeletePage.inputBoxTextSize, BLACK, "year")     # time of the crime
        self.month =    InputBox(self.year.rect.left + 100, self.year.rect.top, 80, DeletePage.inputBoxHieght, DeletePage.inputBoxBackgroundColor, DeletePage.inputBoxTextSize, BLACK, "month")
        self.day =      InputBox(self.year.rect.left + 200, self.year.rect.top, 80, DeletePage.inputBoxHieght, DeletePage.inputBoxBackgroundColor, DeletePage.inputBoxTextSize, BLACK, "day")
        self.hour =     InputBox(self.year.rect.left + 300, self.year.rect.top, 80, DeletePage.inputBoxHieght, DeletePage.inputBoxBackgroundColor, DeletePage.inputBoxTextSize, BLACK, "hour")
        self.minute =   InputBox(self.year.rect.left + 400, self.year.rect.top, 80, DeletePage.inputBoxHieght, DeletePage.inputBoxBackgroundColor, DeletePage.inputBoxTextSize, BLACK, "minute")

        self.active_input_box = None                # active input box
        self.inputBoxGroup = pygame.sprite.Group()  # input box group
        self.inputBoxGroup.add(self.name, self.year, self.month, self.day, self.hour, self.minute)

    def draw(self, surface):
        surface.blit(self.background, self.rect)
        self.close.draw(surface)
        self.name.draw(surface)
        self.ensure.draw(surface)
        self.year.draw(surface)
        self.month.draw(surface)
        self.day.draw(surface)
        self.hour.draw(surface)
        self.minute.draw(surface)
    
    def update(self):
        self.inputBoxGroup.update()

    
    # mouse click event
    def handle_mouse_event(self, event):
        if self.name.rect.collidepoint(event.pos):
            self.active_input_box = self.name
        elif self.year.rect.collidepoint(event.pos):
            self.active_input_box = self.year
        elif self.month.rect.collidepoint(event.pos):
            self.active_input_box = self.month
        elif self.day.rect.collidepoint(event.pos):
            self.active_input_box = self.day
        elif self.hour.rect.collidepoint(event.pos):
            self.active_input_box = self.hour
        elif self.minute.rect.collidepoint(event.pos):
            self.active_input_box = self.minute
        else:
            self.active_input_box = None
        
        self.set_not_active()

                    
    def open_page(self):
        self.is_open = True
    
    def close_page(self):
        self.kill()
    
    def handle_mouse_hover(self, mouse_pos):
        if self.ensure.rect.collidepoint(mouse_pos):
            self.ensure.set_color(LIGHT_RED)
            self.ensure.set_text_color(BLACK)
        elif self.close.rect.collidepoint(mouse_pos):
            self.close.set_color(LIGHT_RED)
            self.close.set_text_color(BLACK)
        else:
            self.ensure.set_color(RED)
            self.ensure.set_text_color(WHITE)
            self.close.set_color(RED)
            self.close.set_text_color(WHITE)

    # set all the input box to "not active" 
    # except the one store in "active_input_box"
    def set_not_active(self):
        for input_box in self.inputBoxGroup:
            input_box.active = False
            # Reset the text to default value
            if input_box.text == '':
                input_box.text = input_box.original_text
                input_box.is_write = False
                input_box.font.set_italic(True)
                input_box.set_text_color(GRAY)
        
        if self.active_input_box:
            self.active_input_box.active = True
            if not self.active_input_box.is_write:   
                    self.active_input_box.text = ''
                    self.active_input_box.is_write = True
                    self.active_input_box.font.set_italic(False)
                    self.active_input_box.set_text_color( self.active_input_box.text_active_color)