import pygame
from function import WINDOW_WIDTH, WINDOW_HEIGHT, blit_alpha

class Alert(pygame.sprite.Sprite):
    def __init__(self, width, height, text, color, font_size, text_color):
        super().__init__()
        self.width = width
        self.height = height
        self.text = text
        self.color = color
        self.font_size = font_size
        self.text_color = text_color
        self.time = pygame.time.get_ticks()

        self.background = pygame.Surface((self.width, self.height // 2))
        self.background.fill(self.color)
        self.image = pygame.image.load("image\\alert.png").convert_alpha()
        self.image = pygame.transform.scale(self.image, (self.height, self.height))
        self.rect = self.image.get_rect()
        self.rect.center = (WINDOW_WIDTH // 2, WINDOW_HEIGHT // 2)

        self.font = pygame.font.Font("font\\calibri-regular.ttf", self.font_size)
        self.text_surface = self.font.render(self.text, True, self.text_color)
        self.text_rect = self.text_surface.get_rect()
        self.text_rect.center = self.rect.center
    
    def draw(self, surface):
        blit_alpha(surface, self.background, (0, self.rect.top + self.height // 4), 150)
        surface.blit(self.image, (self.rect.left, self.rect.top - 90))
        surface.blit(self.text_surface, self.text_rect)
    
    def update(self):
        if pygame.time.get_ticks() - self.time > 2400:
            self.kill()
            return True
        return False
    
