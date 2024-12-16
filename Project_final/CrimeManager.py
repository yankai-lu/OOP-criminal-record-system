import sys
import pygame
from pygame.locals import QUIT
import random

# self file
from function import *
from object import *
from addpage import *
from deletepage import *
from searchpage import *
from alert import *

"""GLOBAL VARIABLES"""

FPS = 120

# mouse button
LEFT = 1
RIGHT = 3

# the width and height of mouse icon 
MOUSEWIDTH = 72
MOUSEHEIGHT = 72

# clock
main_clock = pygame.time.Clock()

blockGroup = pygame.sprite.Group()
"""GLOBAL VARIABLES"""


# Loading page
def Loading_Page():
    # font
    start_font = pygame.font.SysFont(None, 60)

    # global variables
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    start_color = 255           # font color
    start_color_detect = True   # color changing
    
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_SPACE:
                    return
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()



        # color changing
        if start_color_detect == True:
            start_color -= 2
            if start_color < 100:
                start_color_detect = False
        else:
            start_color += 2
            if start_color >= 255:
                start_color_detect = True
        
        # text surface
        start_text_surface = start_font.render("Press space to start CRIME MANAGER!", True, (start_color, start_color, start_color))

        # draw
        window_surface.fill(BLACK)
        window_surface.blit(start_text_surface, (100, WINDOW_HEIGHT/2))

        # update
        pygame.display.update()
        main_clock.tick(FPS)



# Crime Manager
def Crime_Manager():

    # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT
    
    # local setting
    tableHight = 450                                # table height
    tableY = WINDOW_HEIGHT // 2 - tableHight // 2   # table y position
    

    # local variables
    background = pygame.image.load("image\\background.jpg")

    # buttons
    table = Table(100, WINDOW_HEIGHT // 2 - tableHight // 2, 300, tableHight, "image\\table.png")
    add =       Button(table.rect.left + 24, table.rect.top + 100, 253, 50, "New Criminal", BLUE, "font\\calibri-regular.ttf", 35, WHITE)
    delete =    Button(table.rect.left + 24, table.rect.top + 200, 253, 50, "Delete", BLUE, "font\\calibri-regular.ttf", 35, WHITE)
    search =    Button(table.rect.left + 24, table.rect.top + 300, 253, 50, "Search", BLUE, "font\\calibri-regular.ttf", 35, WHITE)
    
    # display table
    board = Table(400, tableY, 850, tableHight, "image\\table3.png")

    # menu loop
    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:            # (這裡可以嘗試做按下倒退鍵時持續刪除)
                    return
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    pass
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()

            # mouse click event
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if add.rect.collidepoint(event.pos):          # add new criminal
                        Add_Criminal_Page()
                    elif delete.rect.collidepoint(event.pos):       # delete criminal
                        Delete_Page()
                    elif search.rect.collidepoint(event.pos):       # search criminal
                        Search_Page(tableY)
                        # 需要return
        
        # mouse hover event
        pos = pygame.mouse.get_pos()
        
        if add.rect.collidepoint(pos):
            add.set_color(LIGHT_BLUE)
            add.set_text_color(BLACK)
        elif delete.rect.collidepoint(pos):
            delete.set_color(LIGHT_BLUE)
            delete.set_text_color(BLACK)
        elif search.rect.collidepoint(pos):
            search.set_color(LIGHT_BLUE)
            search.set_text_color(BLACK)
        else:
            #dropDownMenu.set_color(BLUE)
            #dropDownMenu.set_text_color(WHITE)
            add.set_color(BLUE)
            add.set_text_color(WHITE)
            delete.set_color(BLUE)
            delete.set_text_color(WHITE)
            search.set_color(BLUE)
            search.set_text_color(WHITE)
            for blocks in blockGroup:
                if blocks.handle_mouse_hover(pos):
                    break
                    

        # draw
        window_surface.fill(BLACK)
        window_surface.blit(background, (0, 0))
        table.draw(window_surface)
        blit_alpha(window_surface, board.image, (board.rect), 200)

        add.draw(window_surface)
        delete.draw(window_surface)
        search.draw(window_surface)

        for blocks in blockGroup:
            blocks.draw(window_surface)
        # update
        pygame.display.update()

        main_clock.tick(FPS)

# Add Criminal Page
def Add_Criminal_Page():
    # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    addPage = AddPage()
    addPage.open_page()
    alert = Alert(WINDOW_WIDTH, 200, "", BLACK, 50, WHITE)
    isWarning = False   # warning flag
    warningMessage = "" # warning message

    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:             # ESC鍵關閉視窗
                    addPage.close_page()
                    return
               
                if addPage.active_input_box is None:
                    pass
                elif event.key == pygame.K_RETURN:           # 按下Enter鍵時，將輸入的字串傳送給後端
                    SYSTEM.newCriminal(addPage.stringTransfer().encode('utf-8'), addPage.description.text.encode('utf-8'), int(addPage.year.text), int(addPage.month.text), int(addPage.day.text), int(addPage.hour.text), int(addPage.minute.text), addPage.ID.text.encode('utf-8'), addPage.birthday.text.encode('utf-8'), addPage.gender.text.encode('utf-8'), addPage.location.text.encode('utf-8'), addPage.name.text.encode('utf-8'))
                    print("Successdul add a new criminal.")
                elif event.key == pygame.K_BACKSPACE:        # Check for backspace
                    addPage.active_input_box.text = addPage.active_input_box.text[:-1]
                # Unicode standard is used for string formation 
                else:
                    addPage.active_input_box.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            # 滑鼠點擊事件
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if addPage.close.rect.collidepoint(event.pos):
                        addPage.close_page()
                        return
                    elif addPage.ensure.rect.collidepoint(event.pos):
                        isWarning, warningMessage = addPage.isComplete()
                        # check if the input is complete or not
                        if isWarning:                               
                            warningMessage += " is needed!"
                            alert = Alert(WINDOW_WIDTH, 200, warningMessage, BLACK, 50, WHITE)
                        else:
                            SYSTEM.newCriminal(addPage.stringTransfer().encode('utf-8'), addPage.description.text.encode('utf-8'), int(addPage.year.text), int(addPage.month.text), int(addPage.day.text), int(addPage.hour.text), int(addPage.minute.text), addPage.ID.text.encode('utf-8'), addPage.birthday.text.encode('utf-8'), addPage.gender.text.encode('utf-8'), addPage.location.text.encode('utf-8'), addPage.name.text.encode('utf-8'))
                            addPage.close_page()
                            return
                    else:
                        addPage.handle_mouse_event(event)

        addPage.handle_mouse_hover(pygame.mouse.get_pos())

        for inputbox in addPage.inputBoxGroup:
            if inputbox.is_active():
                inputbox.set_color(InputBox.COLOR_ACTIVE)
            else:
                inputbox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        addPage.draw(window_surface)
        if isWarning:
            alert.draw(window_surface)
            if alert.update():
                isWarning = False

        # update
        pygame.display.update()
        addPage.update()
                
        main_clock.tick(FPS)

def Delete_Page():
    # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    deletePage = DeletePage()
    deletePage.open_page()

    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:              
                if event.key == pygame.K_ESCAPE:
                    deletePage.close_page()
                    return
                
                if deletePage.active_input_box is None:
                    pass
                elif event.key == pygame.K_RETURN:          # 按下Enter鍵時，將輸入的字串傳送給後端
                    SYSTEM.deleteCriminal(deletePage.name.text.encode('utf-8'), int(deletePage.year), int(deletePage.month), int(deletePage.day), int(deletePage.hour), int(deletePage.minute))
                    print("Successdul delete a criminal.")
                elif event.key == pygame.K_BACKSPACE:       # Check for backspace
                    deletePage.active_input_box.text = deletePage.active_input_box.text[:-1]
                # Unicode standard is used for string formation 
                else:
                    deletePage.active_input_box.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if deletePage.close.rect.collidepoint(event.pos):
                        deletePage.close_page()
                        return
                    elif deletePage.ensure.rect.collidepoint(event.pos):
                        SYSTEM.deleteCriminal(deletePage.name.text.encode('utf-8'), int(deletePage.year.text), int(deletePage.month.text), int(deletePage.day.text), int(deletePage.hour.text), int(deletePage.minute.text))
                        deletePage.close_page()
                        return
                    else:
                        deletePage.handle_mouse_event(event)

        # mouse hover event
        pos = pygame.mouse.get_pos()
        deletePage.handle_mouse_hover(pos)

        for inputbox in deletePage.inputBoxGroup:
            if inputbox.is_active():
                inputbox.set_color(InputBox.COLOR_ACTIVE)
            else:
                inputbox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        deletePage.draw(window_surface)

        # update
        pygame.display.update()
        deletePage.update()
                
        main_clock.tick(FPS)

def Search_Page(tableY):
     # global variable
    global WINDOW_WIDTH, WINDOW_HEIGHT

    # local variables
    searchPage = SearchPage()
    blockHight = 60

    # initialize
    searchPage.open_page()

    while True:
        # event detect
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            # 鍵盤 
            elif event.type == pygame.KEYDOWN:        
                if event.key == pygame.K_ESCAPE:
                    searchPage.close_page()
                    return
                
                if searchPage.active_input_box is None:
                    pass
                elif event.key == pygame.K_TAB:
                    pass
                elif event.key == pygame.K_BACKSPACE:       # Check for backspace
                    searchPage.active_input_box.text = searchPage.active_input_box.text[:-1]
                # Unicode standard is used for string formation 
                else:
                    searchPage.active_input_box.text += event.unicode
            # 改變視窗大小
            elif event.type == pygame.VIDEORESIZE:
                WINDOW_WIDTH, WINDOW_HEIGHT = window_surface.get_size()
            # mouse click event
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == LEFT:
                    if searchPage.close.rect.collidepoint(event.pos):
                        searchPage.close_page()
                        return
                    elif searchPage.searchByName.rect.collidepoint(event.pos):
                        # clear the blockGroup
                        blockGroup.empty()

                        # get information from the system
                        recordNumber = SYSTEM.searchbyName(searchPage.name.text.encode('utf-8'), responce_ptr, row, col)
                        '''
                        # test
                        print("pythonGet: ", recordNumber)
                        for i in range(recordNumber * 8):
                            print(ffi.string(responce[i]).decode("utf-8"))
                        '''
                        for i in range(recordNumber):
                            blockGroup.add(Block(450, tableY + 50 + (blockHight+10) * i, 750, blockHight, BLACK, ffi.string(responce[i * 8]).decode("utf-8"), ffi.string(responce[i * 8 + 1]).decode("utf-8"), ffi.string(responce[i * 8 + 2]).decode("utf-8"), ffi.string(responce[i * 8 + 3]).decode("utf-8"), ffi.string(responce[i * 8 + 4]).decode("utf-8"), ffi.string(responce[i * 8 + 5]).decode("utf-8"), ffi.string(responce[i * 8 + 6]).decode("utf-8"), ffi.string(responce[i * 8 + 7]).decode("utf-8")))
                            # x, y, width, height, color, name, id, gender, birth, type, time, location, description
                        
                        searchPage.close_page()
                        return
                    elif searchPage.searchByTime.rect.collidepoint(event.pos):
                        # clear the blockGroup
                        blockGroup.empty()

                        # get information from the system
                        recordNumber = SYSTEM.searchbyTime(int(searchPage.year1.text), int(searchPage.month1.text), int(searchPage.day1.text), int(searchPage.hour1.text), int(searchPage.minute1.text), responce_ptr, row, col)
                        for i in range(recordNumber):
                            blockGroup.add(Block(450, tableY + 50 + (blockHight+10) * i, 750, blockHight, BLACK, ffi.string(responce[i * 8]).decode("utf-8"), ffi.string(responce[i * 8 + 1]).decode("utf-8"), ffi.string(responce[i * 8 + 2]).decode("utf-8"), ffi.string(responce[i * 8 + 3]).decode("utf-8"), ffi.string(responce[i * 8 + 4]).decode("utf-8"), ffi.string(responce[i * 8 + 5]).decode("utf-8"), ffi.string(responce[i * 8 + 6]).decode("utf-8"), ffi.string(responce[i * 8 + 7]).decode("utf-8")))
                        searchPage.close_page()
                        return
                    elif searchPage.searchByTimeCrime.rect.collidepoint(event.pos):
                        # clear the blockGroup
                        blockGroup.empty()

                        # get information from the system
                        recordNumber = SYSTEM.searchbyTimeCrime(int(searchPage.year1.text), int(searchPage.month1.text), int(searchPage.day1.text), int(searchPage.hour1.text), int(searchPage.minute1.text), searchPage.crime.text.encode('utf-8'), responce_ptr, row, col)
                        for i in range(recordNumber):
                            blockGroup.add(Block(450, tableY + 50 + (blockHight+10) * i, 750, blockHight, BLACK, ffi.string(responce[i * 8]).decode("utf-8"), ffi.string(responce[i * 8 + 1]).decode("utf-8"), ffi.string(responce[i * 8 + 2]).decode("utf-8"), ffi.string(responce[i * 8 + 3]).decode("utf-8"), ffi.string(responce[i * 8 + 4]).decode("utf-8"), ffi.string(responce[i * 8 + 5]).decode("utf-8"), ffi.string(responce[i * 8 + 6]).decode("utf-8"), ffi.string(responce[i * 8 + 7]).decode("utf-8")))
                        searchPage.close_page()
                        return
                    elif searchPage.searchByIntervalTime.rect.collidepoint(event.pos):
                        # clear the blockGroup
                        blockGroup.empty()

                        # get information from the system
                        recordNumber = SYSTEM.searchbyIntervalTime(int(searchPage.year1.text), int(searchPage.month1.text), int(searchPage.day1.text), int(searchPage.hour1.text), int(searchPage.minute1.text), int(searchPage.year2.text), int(searchPage.month2.text), int(searchPage.day2.text), int(searchPage.hour2.text), int(searchPage.minute2.text), responce_ptr, row, col)
                        for i in range(recordNumber):
                            blockGroup.add(Block(450, tableY + 50 + (blockHight+10) * i, 750, blockHight, BLACK, ffi.string(responce[i * 8]).decode("utf-8"), ffi.string(responce[i * 8 + 1]).decode("utf-8"), ffi.string(responce[i * 8 + 2]).decode("utf-8"), ffi.string(responce[i * 8 + 3]).decode("utf-8"), ffi.string(responce[i * 8 + 4]).decode("utf-8"), ffi.string(responce[i * 8 + 5]).decode("utf-8"), ffi.string(responce[i * 8 + 6]).decode("utf-8"), ffi.string(responce[i * 8 + 7]).decode("utf-8")))
                        searchPage.close_page()
                        return
                    elif searchPage.searchByIntervalTimeCrime.rect.collidepoint(event.pos):
                        # clear the blockGroup
                        blockGroup.empty()

                        # get information from the system
                        recordNumber = SYSTEM.searchbyIntervalTimeCrime(int(searchPage.year1.text), int(searchPage.month1.text), int(searchPage.day1.text), int(searchPage.hour1.text), int(searchPage.minute1.text), int(searchPage.year2.text), int(searchPage.month2.text), int(searchPage.day2.text), int(searchPage.hour2.text), int(searchPage.minute2.text), searchPage.crime.text.encode('utf-8'), responce_ptr, row, col)
                        for i in range(recordNumber):
                            blockGroup.add(Block(450, tableY + 50 + (blockHight+10) * i, 750, blockHight, BLACK, ffi.string(responce[i * 8]).decode("utf-8"), ffi.string(responce[i * 8 + 1]).decode("utf-8"), ffi.string(responce[i * 8 + 2]).decode("utf-8"), ffi.string(responce[i * 8 + 3]).decode("utf-8"), ffi.string(responce[i * 8 + 4]).decode("utf-8"), ffi.string(responce[i * 8 + 5]).decode("utf-8"), ffi.string(responce[i * 8 + 6]).decode("utf-8"), ffi.string(responce[i * 8 + 7]).decode("utf-8")))
                        searchPage.close_page()
                        return
                    else:
                        searchPage.handle_mouse_event(event)

        searchPage.handle_mouse_hover(pygame.mouse.get_pos())

        for inputbox in searchPage.inputBoxGroup:
            if inputbox.is_active():
                inputbox.set_color(InputBox.COLOR_ACTIVE)
            else:
                inputbox.set_color(InputBox.COLOR_PASSIVE)

        # draw
        searchPage.draw(window_surface)

        # update
        pygame.display.update()
        searchPage.update()
                
        main_clock.tick(FPS)

def main():
    # Waiting for the system getting ready.
    pygame.time.delay(500)

    # test data
    block = Block(450, 135 + 60, 750, 60, BLACK, "Andy", "123", "man", "900910", "Taiwan", "Robbery", "2012/2/22 2:2", "Stole a water bottle.")
    blockGroup.add(block)

    SYSTEM.newCriminal("steal".encode('utf-8'), "Used Thunderbolt and stole power of cities in northeast of America, caused \"Northeast blackout of 2003\".\n".encode('utf-8'), int(2003), int(8), int(14), int(16), int(12), "001".encode('utf-8'), "1996/02/27".encode('utf-8'), "Animal".encode('utf-8'), "Kanto region".encode('utf-8'), "Pikachu".encode('utf-8'))
    SYSTEM.newCriminal("others".encode('utf-8'), "So cute.\n".encode('utf-8'), int(2003), int(8), int(14), int(16), int(12), "001".encode('utf-8'), "1996/02/27".encode('utf-8'), "Animal".encode('utf-8'), "Everywhere".encode('utf-8'), "Pikachu".encode('utf-8'))

    SYSTEM.newCriminal("kill".encode('utf-8'), "He invaded Ukraine and caused a lot of civilian died.\n".encode('utf-8'), int(2022), int(2), int(24), int(5), int(30), "002".encode('utf-8'), "1952/10/07".encode('utf-8'), "Man".encode('utf-8'), "Ukraine".encode('utf-8'), "Putin".encode('utf-8'))
    
    blockGroup.add(Block(450, 135 + 130, 750, 60, BLACK, "Pikachu", "001", "Animal", "1996/02/27", "Kanto region", "steal", "2003/8/14 16:12", "Used Thunderbolt and stole power of cities in northeast of America, caused \"Northeast blackout of 2003\".\n"))
    blockGroup.add(Block(450, 135 + 200, 750, 60, BLACK, "Pikachu", "001", "Animal", "1996/02/27", "Everywhere", "others", "2003/8/14 16:12", "So cute.\n"))
    blockGroup.add(Block(450, 135 + 270, 750, 60, BLACK, "Putin", "002", "man", "1952/10/07", "Ukraine", "kill", "2022/2/24 5:30", "He invaded Ukraine and caused a lot of civilian died.\n"))

    Loading_Page()

    Crime_Manager()

if __name__ == '__main__':    
    main()