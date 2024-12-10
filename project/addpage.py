from function import pygame, WINDOW_WIDTH, WINDOW_HEIGHT, WHITE, BLACK, LIGHT_BLUE, BLUE, RED, PURPLE, LIGHT_PURPLE, GRAY
from object import Button, InputBox

class AddPage(pygame.sprite.Sprite):
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

        self.background = pygame.Surface((AddPage.WIDTH, AddPage.HEIGHT))
        self.background.fill(GRAY)
        self.rect = self.background.get_rect()
        self.rect.center = (WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2) # set the center of the page to the center of the window
        self.x = self.rect.topleft[0]
        self.y = self.rect.topleft[1]
        
        # buttons
        self.close = Button(self.x + AddPage.WIDTH - 40, self.y + 0, 40, 40, "x", RED, None, 40, WHITE)
        
        # drop down menu
        self.crime = Button(self.x + 400, self.y + 60, 200, 40, "(Crime Type)", BLUE, "font\\calibri-regular.ttf", 25, WHITE)
        self.selection = pygame.sprite.Group()
        for i in range(AddPage.selectionTypeNumber):
            self.selection.add(Button(self.crime.rect.topleft[0], self.crime.rect.topleft[1] + 40 * (i+1), 200, 40, AddPage.selectionType[i], PURPLE, "font\\calibri-regular.ttf", 25, WHITE))
        self.is_crime_open = False

        # input boxes
        self.name = InputBox(self.x + 100, self.y + 10, 200, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "name")      # criminal basic information
        self.ID = InputBox(self.x + 100, self.y + 60, 200, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "ID")
        self.gender = InputBox(self.x + 100, self.y + 110, 200, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "gender")
        self.birthday = InputBox(self.x + 100, self.y + 160, 200, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "birthday") # criminal personal information

        self.year =     InputBox(self.x + 400, self.y + 10, 80, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "year")     # time of the crime
        self.month =    InputBox(self.year.rect.left + 100, self.year.rect.top, 80, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "month")
        self.day =      InputBox(self.year.rect.left + 200, self.year.rect.top, 80, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "day")
        self.hour =     InputBox(self.year.rect.left + 300, self.year.rect.top, 80, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "hour")
        self.minute =   InputBox(self.year.rect.left + 400, self.year.rect.top, 80, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "minute")
               
        self.location = InputBox(self.x + 100, self.y + 310, 500, AddPage.inputBoxHieght, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "location")
        self.description = InputBox(self.x + 100, self.y + 360, 500, AddPage.inputBoxHieght * 2, AddPage.inputBoxBackgroundColor, AddPage.inputBoxTextSize, BLACK, "description...")
        
        self.active_input_box = None                # active input box
        self.inputBoxGroup = pygame.sprite.Group()  # input box group
        self.inputBoxGroup.add(self.name, self.ID, self.year, self.month, self.day, self.hour, self.minute, self.gender, self.birthday, self.location, self.description)

    def draw(self, surface):
        surface.blit(self.background, self.rect)
        self.close.draw(surface)
        self.crime.draw(surface)
        self.name.draw(surface)
        self.ID.draw(surface)
        self.birthday.draw(surface)
        self.gender.draw(surface)
        self.location.draw(surface)
        self.description.draw(surface)
        self.year.draw(surface)
        self.month.draw(surface)
        self.day.draw(surface)
        self.hour.draw(surface)
        self.minute.draw(surface)
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
        elif self.ID.rect.collidepoint(event.pos):
            self.active_input_box = self.ID
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
        elif self.gender.rect.collidepoint(event.pos):
            self.active_input_box = self.gender
        elif self.birthday.rect.collidepoint(event.pos):
            self.active_input_box = self.birthday
        elif self.location.rect.collidepoint(event.pos):
            self.active_input_box = self.location
        elif self.description.rect.collidepoint(event.pos):
            self.active_input_box = self.description
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