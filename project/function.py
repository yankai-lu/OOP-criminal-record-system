import pygame

WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
BLUE = (80, 105, 155)
LIGHT_BLUE = (173, 216, 230)
PURPLE = (128, 0, 128)
LIGHT_PURPLE = (230, 120, 230)

# 初始化
pygame.init()
pygame.mixer.init()
pygame.font.init()

# load window surface
window_surface = pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT), pygame.RESIZABLE)
pygame.display.set_caption('Crime Manager')

# Draw a image that is transparent
def blit_alpha(target, source, location, opacity): # window 圖片 位置 透明度
    x = location[0]
    y = location[1]
    temp = pygame.Surface((source.get_width(), source.get_height())).convert()
    temp.blit(target, ( -x, - y ))
    temp.blit(source, (0, 0))
    temp.set_alpha(opacity)        
    target.blit(temp, location)