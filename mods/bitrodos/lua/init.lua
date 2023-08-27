require("bitrodos", "rendering")

system.add_hook("tick", function(delta_time)
    if input.is_key_down(Keys.W) then
        CAMERA:move(Direction.NORTH, delta_time)
    end
    if input.is_key_down(Keys.A) then
        CAMERA:move(Direction.WEST, delta_time)
    end
    if input.is_key_down(Keys.S) then
        CAMERA:move(Direction.SOUTH, delta_time)
    end
    if input.is_key_down(Keys.D) then
        CAMERA:move(Direction.EAST, delta_time)
    end
    if input.is_key_down(Keys.SPACE) then
        CAMERA:move(Direction.TOP, delta_time)
    end
    if input.is_key_down(Keys.SHIFT) then
        CAMERA:move(Direction.BOTTOM, delta_time)
    end
end)

local first_mouse = true
local last_x = 800.0/2.0
local last_y = 600.0/2.0

system.add_hook("cursor", function(x_pos, y_pos, delta_time) 
    if first_mouse then
        last_x = x_pos
        last_y = y_pos
        first_mouse = false
    end

    local x_offset = x_pos - last_x
    local y_offset = last_y - y_pos

    CAMERA:rotate(x_offset, y_offset)

    last_x = x_pos
    last_y = y_pos
end)

system.add_hook("resize", function(width, height)
    CAMERA:resize(width, height)
end)
