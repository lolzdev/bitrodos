local shader = graphics.load_shader("bitrodos", "main.vert", "main.frag")

log.info("Loaded main shader")

system.add_hook("render", function()
    graphics.use_shader(shader);
end);

