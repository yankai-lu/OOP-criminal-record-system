from function import pygame, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE, BLACK, LIGHT_BLUE, BLUE, RED, PURPLE, LIGHT_PURPLE, GRAY
from object import Button, InputBox


class SearchPage(pygame.sprite.Sprite):
    # page size
    WIDTH = 1000
    HEIGHT = 600

    selectionType = ["Theft", "Robbery", "Fraud", "Murder", "others..."]
    selectionTypeNumber = 5

    inputBoxHieght = 40
    inputBoxTextSize = 25
    inputBoxBackgroundColor = WHITE

    def __init__(self):
        super().__init__()
        self.is_open = False    # page status

        self.background = pygame.Surface((SearchPage.WIDTH, SearchPage.HEIGHT))
        self.background.fill(GRAY)
        self.rect = self.background.get_rect()
        self.rect.center = (WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2) # set the center of the page to the center of the window
        self.x = self.rect.topleft[0]
        self.y = self.rect.topleft[1]
        
        # buttons
        self.close = Button(self.x + SearchPage.WIDTH - 40, self.y + 0, 40, 40, "x", RED, None, 40, WHITE)
        
        # drop down menu
        self.crime = Button(self.x + 400, self.y + 110, 200, 40, "(Crime Type)", BLUE, "font\\calibri-regular.ttf", 25, WHITE)
        self.selection = pygame.sprite.Group()
        for i in range(SearchPage.selectionTypeNumber):
            self.selection.add(Button(self.crime.rect.topleft[0], self.crime.rect.topleft[1] + 40 * (i+1), 200, 40, SearchPage.selectionType[i], PURPLE, "font\\calibri-regular.ttf", 25, WHITE))
        self.is_crime_open = False

        # input boxes
        self.name = InputBox(self.x + 100, self.y + 10, 200, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "name")      # criminal basic information

        self.year1 =     InputBox(self.x + 400, self.y + 10, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "year")     # time of the crime
        self.month1 =    InputBox(self.year1.rect.left + 100, self.year1.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "month")
        self.day1 =      InputBox(self.year1.rect.left + 200, self.year1.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "day")
        self.hour1 =     InputBox(self.year1.rect.left + 300, self.year1.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "hour")
        self.minute1 =   InputBox(self.year1.rect.left + 400, self.year1.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "minute")

        self.year2 =     InputBox(self.x + 400, self.y + 60, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "year")     # time of the crime
        self.month2 =    InputBox(self.year2.rect.left + 100, self.year2.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "month")
        self.day2 =      InputBox(self.year2.rect.left + 200, self.year2.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "day")
        self.hour2 =     InputBox(self.year2.rect.left + 300, self.year2.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "hour")
        self.minute2 =   InputBox(self.year2.rect.left + 400, self.year2.rect.top, 80, SearchPage.inputBoxHieght, SearchPage.inputBoxBackgroundColor, SearchPage.inputBoxTextSize, BLACK, "minute")
        
        self.active_input_box = None                # active input box
        self.inputBoxGroup = pygame.sprite.Group()  # input box group
        self.inputBoxGroup.add(self.name, self.year1, self.month1, self.day1, self.hour1, self.minute1, self.year2, self.month2, self.day2, self.hour2, self.minute2)

    def draw(self, surface):
        surface.blit(self.background, self.rect)
        self.close.draw(surface)
        self.crime.draw(surface)
        self.name.draw(surface)
        self.year1.draw(surface)
        self.month1.draw(surface)
        self.day1.draw(surface)
        self.hour1.draw(surface)
        self.minute1.draw(surface)
        self.year2.draw(surface)
        self.month2.draw(surface)
        self.day2.draw(surface)
        self.hour2.draw(surface)
        self.minute2.draw(surface)
        if(self.is_crime_open):
            for option in self.selection:
                option.draw(surface)
    
    def update(self):
        self.inputBoxGroup.update()

    # mouse click event
    def handle_mouse_event(self, event):
        if self.crime.rect.collidepoint(event.pos):
            self.is_crime_open = not self.is_crime_open
        elif self.name.rect.collidepoint(event.pos):
            self.active_input_box = self.name
        elif self.year1.rect.collidepoint(event.pos):
            self.active_input_box = self.year1
        elif self.month1.rect.collidepoint(event.pos):
            self.active_input_box = self.month1
        elif self.day1.rect.collidepoint(event.pos):
            self.active_input_box = self.day1
        elif self.hour1.rect.collidepoint(event.pos):
            self.active_input_box = self.hour1
        elif self.minute1.rect.collidepoint(event.pos):
            self.active_input_box = self.minute1
        elif self.year2.rect.collidepoint(event.pos):
            self.active_input_box = self.year2
        elif self.month2.rect.collidepoint(event.pos):
            self.active_input_box = self.month2
        elif self.day2.rect.collidepoint(event.pos):
            self.active_input_box = self.day2
        elif self.hour2.rect.collidepoint(event.pos):
            self.active_input_box = self.hour2
        elif self.minute2.rect.collidepoint(event.pos):
            self.active_input_box = self.minute2
        elif self.is_crime_open:
            for option in self.selection:
                if option.rect.collidepoint(event.pos):
                    self.crime.set_text(option.text)
            self.is_crime_open = False
            self.active_input_box = None
        else:
            self.active_input_box = None
        
        self.set_not_active()
    
    # mouse hover event
    # change the color of the button when mouse hover
    def handle_mouse_hover(self, mouse_pos):
        if(self.is_crime_open):
            self.crime.set_color(LIGHT_BLUE)
            self.crime.set_text_color(BLACK)
            for option in self.selection:
                if option.rect.collidepoint(mouse_pos): 
                    option.set_color(LIGHT_PURPLE)
                    option.set_text_color(BLACK)
                else:
                    option.set_color(PURPLE)
                    option.set_text_color(WHITE)
        elif(self.crime.rect.collidepoint(mouse_pos)):
            self.crime.set_color(LIGHT_BLUE)
            self.crime.set_text_color(BLACK)
        else:
            self.crime.set_color(BLUE)
            self.crime.set_text_color(WHITE)
                    
    def open_page(self):
        self.is_open = True
    
    def close_page(self):
        self.kill()
    
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