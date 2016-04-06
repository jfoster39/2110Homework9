typedef struct{
    int width;
    int height;
    int row;
    int col;
} EntityClass;

const int max_projectiles = 100;
const int max_enemies     = 100;
int enemy_num             = 0;
int projectile_num        = 0;
EntityClass projectiles[102];
EntityClass enemies[102];

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

void generate_enemy( int row, int col )
{
    EntityClass enemy;
    initialize_entity( &enemy, ENEMY_WIDTH, ENEMY_HEIGHT, row, col );

    enemies[enemy_num] = enemy;
    enemy_num++;
}

void fire_weapon( EntityClass* entity )
{
    EntityClass projectile;
    initialize_entity( &projectile, 8, 3, entity->row + 8, entity->col + 8 );

    projectiles[projectile_num] = projectile;
    projectile_num++;
} 

void update_projectiles()
{
    for( int i = 0; i < projectile_num; i++ )
    {
        if( projectiles[i].row != 0 )
        {
            projectiles[i].col += 3;
            draw_entity( &projectiles[i], enemy );
        }
    }
}

void update_enemies()
{
    for( int i = 0; i < enemy_num; i++ )
    {
        if( enemies[i].row != 0 )
        {
            enemies[i].col--;
            draw_entity( &enemies[i], enemy );
        }
    }
}

// If true, collision happened. 
int detect_collision( EntityClass* entity_1, EntityClass* entity_2 )
{
    if( entity_1->col < entity_2->col + entity_2->width      && 
            entity_1->col + entity_1->width > entity_2->col  &&
            entity_1->row < entity_2->row + entity_2->height &&
            entity_1->height + entity_1->row > entity_2->row )
    {
        return 1;
    }

    return 0;
}

void check_collisions() {
    for( int i = 0; i < max_enemies; i++ )
    {
        for( int j = 0; j < projectile_num; j++ )
        {
            if( detect_collision( &enemies[i], &projectiles[j] ) == 1 )
            {
                enemies[i]     = enemies[max_enemies+1];
                projectiles[j] = projectiles[max_projectiles+1];
                break;
            }
        }
    }
}

void remove_old_projectiles()
{
    for( int i = 0; i < projectile_num; i++ )
    {
        if( projectiles[i].col > 240 )
        {
            projectiles[i] = projectiles[max_projectiles+1];
            break;
        }
    }
}

void remove_old_enemies()
{
    for( int i = 0; i < enemy_num; i++ )
    {
        if( enemies[i].col == 1 )
        {
            enemies[i] = enemies[max_enemies+1];
            break;
        }
    }
}

// If true, player is dead.
int is_player_dead( EntityClass* player_ship )
{
    for( int i = 0; i < enemy_num; i++ )
    {
        if( enemies[i].row != 0 )
        {
            if( detect_collision( player_ship, &enemies[i] ) == 1 )
            {
                return 1;
            }
        }
    }

    return 0;
}
