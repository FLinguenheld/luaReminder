local WINDOW_WIDTH = 800
local WINDOW_HEIGHT = 600

local x, y = 100, 100
local dx, dy = 50, 50

--------------------------------------------------
-- Update function
--------------------------------------------------
function update(delta_time)

    if x >= WINDOW_WIDTH or x <= 0 then
        dx = dx * -1
    end

    if y >= WINDOW_HEIGHT or y <= 0 then
        dy = dy * -1
    end

    x = x + dx * delta_time
    y = y + dy * delta_time

    --print("Update called in lua ! " .. delta_time)
    set_player_pos(x, y)
end

--------------------------------------------------
-- Render function
--------------------------------------------------
function render()
    
end
