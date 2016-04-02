typedef struct{
    int width;
    int height;
    int row;
    int col;
} EntityClass;

const int max_projectiles = 10;
EntityClass projectiles[max_projectiles];

void initialize_entity( EntityClass* entity, int width, int height, int row, int col )
{
    entity->width  = width;
    entity->height = height;
    entity->row    = row;
    entity->col    = col;
}

int get_row( EntityClass* entity )
{
    return entity->row;
}

int get_col( EntityClass* entity )
{
    return entity->col;
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

void fire_weapon( EntityClass* entity )
{
    EntityClass projectile;
    initialize_entity( &projectile, 3, 8, entity->row + 8, entity->col + 8 );

    for( int i = 0; i < max_projectiles; i++ )
    {
        if( projectiles[i].row == 0 )
        {
            projectiles[i] = projectile;
            break;
        }
    }

    drawImage3( 0, 0, ENEMY_WIDTH, ENEMY_HEIGHT, enemy );
} 

void update_projectiles()
{
    for( int i = 0; i < max_projectiles; i++ )
    {
        if( projectiles[i].row != 0 )
        {
            projectiles[i].col += 3;
            //drawRect( projectiles[i].row, projectiles[i].col, projectiles[i].width, projectiles[i].height, BLUE );
            drawImage3( projectiles[i].row, projectiles[i].col, ENEMY_WIDTH, ENEMY_HEIGHT, enemy );
        }
    }
}
