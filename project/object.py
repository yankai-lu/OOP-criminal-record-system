import pygame

class Button(pygame.sprite.Sprite):
    def __init__(self, x, y, width, height, text, color, font, font_size, text_color):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.text = text
        self.color = color
        self.font = font
        self.font_size = font_size
        self.text_color = text_color
        self.image = pygame.Surface((self.width, self.height))
        self.image.fill(self.color)
        self.rect = self.image.get_rect()
        self.rect.topleft = (self.x, self.y)
        self.font = pygame.font.Font("Tightones.otf", self.font_size)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center
        self.text_surface.blit(self.image, self.text_rect)
        
    def update(self):
        pass

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
        self.color = color
        self.image.fill(self.color)

    def get_color(self):
        return self.color
    
    def set_text_color(self, text_color):
        self.text_color = text_color
        self.text_surface = self.font.render(self.text, True, self.text_color)

    def set_font(self, font):
        self.font = pygame.font.Font(font, self.font_size)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center
    


class InputBox(pygame.sprite.Sprite):
    COLOR_ACTIVE = pygame.Color('lightskyblue3')    # color_active stores color(lightskyblue3) which 
                                                    # gets active when input box is clicked by user 
   
    COLOR_PASSIVE = pygame.Color('chartreuse4')     # color_passive store color(chartreuse4) which is 

    def __init__(self, x, y, width, height, color, font_size, text_color):
        super().__init__()
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.text = '( Click here to type word )'
        self.color = color
        self.font = pygame.font.SysFont(None, font_size)
        self.font_size = font_size
        self.text_color = text_color

        self.image = pygame.Surface((self.width, self.height))
        self.image.fill(self.color)
        self.rect = self.image.get_rect()
        self.rect.topleft = (self.x, self.y)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center

        self.active = False
        
        
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
        self.text_rect.center = self.rect.center
        self.image.fill(self.color)

    def set_color(self, color):
        self.color = color
        self.image.fill(self.color)

    def get_color(self):
        return self.color
    
    def set_text_color(self, text_color):
        self.text_color = text_color
        self.text_surface = self.font.render(self.text, True, self.text_color)

    def set_font(self, font):
        self.font = pygame.font.Font(font, self.font_size)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center

    def handle_event(self, event):
        if event.type == pygame.MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                self.active = True
                self.text = ''
            else:
                self.active = False
                self.text = '( Click here to type word )'
            
        if event.type == pygame.KEYDOWN:
            if self == self.active:
                if event.key == pygame.K_BACKSPACE:
                    self.text = self.text[:-1]
                else:
                    self.text += event.unicode
    
    def is_active(self):
        return self.active