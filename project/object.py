import pygame
from function import GRAY, WHITE, LIGHT_GRAY

class Button(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, text, color, font, font_size, text_color):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.text = text
        self.color = color
        self.font_size = font_size
        self.text_color = text_color

        self.image = pygame.Surface((self.width, self.height))
        self.image.fill(self.color)
        self.rect = self.image.get_rect()
        self.rect.topleft = (self.x, self.y)

        if font == None:
            self.font = pygame.font.SysFont(None, self.font_size)
        else:
            self.font = pygame.font.Font(font, self.font_size)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center
        self.text_surface.blit(self.image, self.text_rect)

    def draw(self, surface):
        surface.blit(self.image, self.rect)
        surface.blit(self.text_surface, self.text_rect)

    def set_text(self, text):
        self.text = text
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center
        self.image.fill(self.color)

    def set_color(self, color):
        if color != self.color:
            self.color = color
            self.image.fill(self.color)

    def get_color(self):
        return self.color
    
    def set_text_color(self, text_color):
        if text_color != self.text_color:
            self.text_color = text_color
            self.text_surface = self.font.render(self.text, True, self.text_color)
    '''
    def set_font(self, font):
        self.font = pygame.font.Font(font, self.font_size)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center
    '''
    


class InputBox(pygame.sprite.Sprite):
    COLOR_ACTIVE =  pygame.Color(WHITE)             # color_active stores color(lightskyblue3) which 
                                                    # gets active when input box is clicked by user 
   
    COLOR_PASSIVE = pygame.Color(LIGHT_GRAY)   # color_passive store color(chartreuse4) which is 

    def __init__(self, x, y, width, height, color, font_size, text_color, message):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.text = message
        self.original_text = message
        self.color = color
        self.font = pygame.font.SysFont(None, font_size)
        self.font_size = font_size
        self.text_color = GRAY
        self.text_active_color = text_color

        self.image = pygame.Surface((self.width, self.height))
        self.image.fill(self.color)
        self.rect = self.image.get_rect()
        self.rect.topleft = (self.x, self.y)

        self.font.set_italic(True)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()

        self.active = False
        self.is_write = False
        
        
    def update(self):
        self.text_surface = self.font.render(self.text, True, self.text_color)
        pass

    def draw(self, surface):
        surface.blit(self.image, self.rect)
        surface.blit(self.text_surface, (self.rect.left + 10, self.rect.centery - self.text_rect.height // 2))

    def set_text(self, text):
        self.text = text
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.image.fill(self.color)

    def set_color(self, color):
        if color != self.color:
            self.color = color
            self.image.fill(self.color)

    def get_color(self):
        return self.color
    
    def set_text_color(self, text_color):
        if text_color != self.text_color:
            self.text_color = text_color
            self.text_surface = self.font.render(self.text, True, self.text_color)

    def handle_mouse_event(self, event) -> bool:
        if self.rect.collidepoint(event.pos):
            self.active = True
            # clear the input box for typing
            if not self.is_write:   
                self.text = ''
                self.is_write = True
                self.font.set_italic(False)
                self.set_text_color(self.text_active_color)
            return True
        else:
            self.active = False
            # Reset the text to default value
            if self.text == '':
                self.text = self.original_text
                self.is_write = False
                self.font.set_italic(True)
                self.set_text_color(GRAY)
            return False
    
    def is_active(self):
        return self.active

class Table(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, image):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        if(image == None):
            self.raw_image = pygame.Surface((width, height))
            self.image = self.raw_image
            self.image.fill(GRAY)
        else:
            self.raw_image = pygame.image.load(image).convert_alpha()
            self.image = pygame.transform.scale(self.raw_image, (width, height))
        
        self.rect = self.image.get_rect()
        self.rect.topleft = (x, y)
    
    def draw(self, surface):
        surface.blit(self.image, self.rect)