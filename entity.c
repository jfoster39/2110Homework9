typedef struct {
    int width;
    int height;
    int row;
    int col;
} EntityClass;

void initialize_entity( EntityClass* entity, int width, int height, int row, int col )
{
    entity->width  = width;
    entity->height = height;
    entity->row    = row;
    entity->col    = col;
}

void move_entity( EntityClass* entity, int row_offset, int col_offset )
{
    entity->row = entity->row + row_offset;
    entity->col = entity->col + col_offset;
}

void draw_entity( EntityClass* entity, const u16* image )
{
    drawImage3( 
        entity->row, 
        entity->col, 
        entity->width, 
        entity->height, 
        image 
    );
}
