CAMERA = Camera(Vec3(0, 0, 0), -90, 0) -- Global variable for the Camera object

local shader = graphics.load_shader("bitrodos", "main.vert", "main.frag")

system.add_hook("render", function(delta_time)
    graphics.use_shader(shader); -- Use the main shader program

    CAMERA:use(shader) -- Apply camera transformations
end);

