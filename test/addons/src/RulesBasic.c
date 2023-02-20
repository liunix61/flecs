#include <addons.h>

void RulesBasic_1_fact_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_tag_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_component_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, ent, Position, TgtA, {10, 20});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent), RelB(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position(ent), Velocity(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, ent, Position, {10, 20});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, ent, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_tag_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, TgtA), RelA(ent, TgtB)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_component_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position(ent, TgtA), Position(ent, TgtB)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, ent, Position, TgtA, {10, 20});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, ent, Position, TgtB, {30, 40});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_uint(ecs_pair(ecs_id(Position), TgtB), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent1), RelB(ent2)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent1, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent2, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position(ent1), Velocity(ent2)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, ent1, Position, {10, 20});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, ent2, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p->x, 10);
        test_int(p->y, 20);
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v->x, 1);
        test_int(v->y, 2);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_tag_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent1, TgtA), RelA(ent2, TgtB)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent1, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent2, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_component_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position(ent1, TgtA), Position(ent2, TgtB)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, ent1, Position, TgtA, {10, 20});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, ent2, Position, TgtB, {30, 40});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(ecs_pair(ecs_id(Position), TgtB), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelA);
    ecs_add(world, ent, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_pair_any_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_pair_any_rel() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_fact_w_pair_any_rel_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");
    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent), _(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelA);
    ecs_add(world, ent, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_pair_any_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, _), RelA(ent, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_pair_any_rel() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent, TgtA), _(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_same_src_w_pair_any_rel_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");
    ecs_add_pair(world, ent, RelA, TgtA);
    ecs_add_pair(world, ent, RelB, TgtA);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent, _), _(ent, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent1), _(ent2)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent1, RelA);
    ecs_add(world, ent1, RelB);
    ecs_add(world, ent2, RelA);
    ecs_add(world, ent2, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(EcsWildcard, ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_pair_any_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent1, _), RelA(ent2, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent1, RelA, TgtA);
    ecs_add_pair(world, ent1, RelA, TgtB);
    ecs_add_pair(world, ent2, RelA, TgtA);
    ecs_add_pair(world, ent2, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_pair_any_rel() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent1, _), RelA(ent2, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent1, RelA, TgtA);
    ecs_add_pair(world, ent1, RelA, TgtB);
    ecs_add_pair(world, ent2, RelA, TgtA);
    ecs_add_pair(world, ent2, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_facts_other_src_w_pair_any_rel_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent1 = ecs_new_entity(world, "ent1");
    ecs_add_pair(world, ent1, RelA, TgtA);
    ecs_add_pair(world, ent1, RelB, TgtA);
    ecs_entity_t ent2 = ecs_new_entity(world, "ent2");
    ecs_add_pair(world, ent2, RelA, TgtA);
    ecs_add_pair(world, ent2, RelB, TgtA);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "_(ent1, _), _(ent2, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 1));
        test_uint(ent1, ecs_field_src(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(ent2, ecs_field_src(&it, 2));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_tag_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_component_pair() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position($this, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, e1, Position, TgtA, {10, 20});
    ecs_set_pair(world, e2, Position, TgtA, {30, 40});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_tag_2_tables() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_component_2_tables() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 10); test_int(p[0].y, 20);
        }

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 30); test_int(p[0].y, 40);
        }

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_tag_pair_2_tables() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_this_src_w_component_pair_2_tables() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_TAG(world, TgtA)
    ECS_TAG(world, FragmentA);
    ECS_TAG(world, FragmentB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_add(world, e1, FragmentA);
    ecs_add(world, e2, FragmentB);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position($this, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set_pair(world, e1, Position, TgtA, {10, 20});
    ecs_set_pair(world, e2, Position, TgtA, {30, 40});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 10); test_int(p[0].y, 20);
        }

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(ecs_id(Position), TgtA), ecs_field_id(&it, 1));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        {
            const Position *p = ecs_field(&it, Position, 1);
            test_assert(p != NULL);
            test_int(p[0].x, 30); test_int(p[0].y, 40);
        }

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_this_src_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this), RelB($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);
    ecs_add(world, e1, RelB);
    ecs_add(world, e2, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_this_src_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position($this), Velocity($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});

    ecs_set(world, e1, Velocity, {1, 2});
    ecs_set(world, e2, Velocity, {3, 4});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v[0].x, 1); test_int(v[0].y, 2);
        test_int(v[1].x, 3); test_int(v[1].y, 4);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_this_src_ent_src_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this), RelB(e3)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e3, ecs_field_src(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_this_src_ent_src_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Position($this), Velocity(e3)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});
    ecs_set(world, e3, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Position), ecs_field_id(&it, 1));
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e3, ecs_field_src(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Position *p = ecs_field(&it, Position, 1);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        const Velocity *v = ecs_field(&it, Velocity, 2);
        test_assert(v != NULL);
        test_int(v[0].x, 1); test_int(v[0].y, 2);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_ent_src_this_src_w_tag() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelB(e3), RelA($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e2, RelA);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelB, ecs_field_id(&it, 1));
        test_uint(RelA, ecs_field_id(&it, 2));
        test_uint(e3, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_ent_src_this_src_w_component() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_entity(world, "e3");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "Velocity(e3), Position($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_set(world, e1, Position, {10, 20});
    ecs_set(world, e2, Position, {30, 40});
    ecs_set(world, e3, Velocity, {1, 2});

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_id(Velocity), ecs_field_id(&it, 1));
        test_uint(ecs_id(Position), ecs_field_id(&it, 2));
        test_uint(e3, ecs_field_src(&it, 1));
        test_uint(0, ecs_field_src(&it, 2));
        test_uint(e1, it.entities[0]);
        test_uint(e2, it.entities[1]);
        const Velocity *v = ecs_field(&it, Velocity, 1);
        test_assert(v != NULL);
        test_int(v[0].x, 1); test_int(v[0].y, 2);
        const Position *p = ecs_field(&it, Position, 2);
        test_assert(p != NULL);
        test_int(p[0].x, 10); test_int(p[0].y, 20);
        test_int(p[1].x, 30); test_int(p[1].y, 40);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_recycled_tag() {
    ecs_world_t *world = ecs_init();

    ecs_delete(world, ecs_new_id(world));
    ECS_TAG(world, RelA);
    test_assert((uint32_t)RelA != RelA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_recycled_src() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);

    ecs_delete(world, ecs_new_id(world));
    ecs_entity_t ent = ecs_new_entity(world, "ent");
    test_assert((uint32_t)ent != ent);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_recycled_pair_rel() {
    ecs_world_t *world = ecs_init();

    ecs_delete(world, ecs_new_id(world));
    ECS_TAG(world, RelA);
    test_assert((uint32_t)RelA != RelA);
    ECS_TAG(world, TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_recycled_pair_tgt() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ecs_delete(world, ecs_new_id(world));
    ECS_TAG(world, TgtA);
    test_assert((uint32_t)TgtA != TgtA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, ent, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this), *($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e1, RelB);
    
    ecs_add(world, e2, RelA);
    ecs_add(world, e2, RelB);
    ecs_add(world, e2, RelC);

    ecs_add(world, e3, RelA);
    ecs_add(world, e3, RelB);
    ecs_add(world, e3, RelC);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelA, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelA, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelB, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(RelC, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_pair_rel_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA), *($this, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e1, RelB, TgtB);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e2, RelC, TgtA);
    ecs_add_pair(world, e2, RelC, TgtB);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);
    ecs_add_pair(world, e3, RelC, TgtA);
    ecs_add_pair(world, e3, RelC, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelC, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_pair_tgt_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA), RelA($this, *)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelA, TgtC);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelA, TgtC);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtC), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_pair_rel_tgt_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA), *($this, *)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this), _($this)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e1, RelB);
    
    ecs_add(world, e2, RelA);
    ecs_add(world, e2, RelB);
    ecs_add(world, e2, RelC);

    ecs_add(world, e3, RelA);
    ecs_add(world, e3, RelB);
    ecs_add(world, e3, RelC);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(EcsWildcard, ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_pair_rel_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA), _($this, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e1, RelB, TgtB);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e2, RelC, TgtA);
    ecs_add_pair(world, e2, RelC, TgtB);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);
    ecs_add_pair(world, e3, RelC, TgtA);
    ecs_add_pair(world, e3, RelC, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, TgtA), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_pair_tgt_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA), RelA($this, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelA, TgtC);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelA, TgtC);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(RelA, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_this_src_w_pair_rel_tgt_any() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_id(world);
    ecs_entity_t e2 = ecs_new_id(world);
    ecs_entity_t e3 = ecs_new_id(world);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA($this, TgtA), _($this, _)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    
    ecs_add_pair(world, e2, RelA, TgtA);
    ecs_add_pair(world, e2, RelA, TgtB);
    ecs_add_pair(world, e2, RelB, TgtA);

    ecs_add_pair(world, e3, RelA, TgtA);
    ecs_add_pair(world, e3, RelA, TgtB);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(1, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e1, it.entities[0]);

        test_bool(true, ecs_rule_next(&it));
        test_uint(2, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(ecs_pair(EcsWildcard, EcsWildcard), ecs_field_id(&it, 2));
        test_uint(0, ecs_field_src(&it, 1));
        test_uint(e2, it.entities[0]);
        test_uint(e3, it.entities[1]);

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_ent_src_w_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "*(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelA);
    ecs_add(world, e1, RelB);
    ecs_add(world, e1, RelC);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelB, ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelC, ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_ent_src_w_pair_rel_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "*(ent, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e1, RelC, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelC, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_ent_src_w_pair_tgt_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);
    ECS_TAG(world, TgtC);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent, *)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelA, TgtC);
    ecs_add_pair(world, e1, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtC), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_ent_src_w_pair_rel_tgt_wildcard() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, RelC);
    ECS_TAG(world, TgtA);
    ECS_TAG(world, TgtB);

    ecs_entity_t e1 = ecs_new_entity(world, "ent");
    ecs_add_pair(world, e1, RelA, TgtA);
    ecs_add_pair(world, e1, RelA, TgtB);
    ecs_add_pair(world, e1, RelB, TgtA);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "*(ent, *)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(ecs_id(EcsIdentifier), EcsName), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtB), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelB, TgtA), ecs_field_id(&it, 1));
        test_uint(e1, ecs_field_src(&it, 1));

        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_any_src() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, Tag);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(_)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_entity_t e1 = ecs_new(world, RelA);
    ecs_add_id(world, e1, Tag);
    ecs_new(world, RelA);
    ecs_new(world, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_1_any_src_w_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, Tag);
    ECS_TAG(world, TgtA);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(_, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_entity_t e1 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_add(world, e1, Tag);
    ecs_new_w_pair(world, RelA, TgtA);
    ecs_new_w_pair(world, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_any_src() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, Tag);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(_), RelB(_)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_entity_t e1 = ecs_new(world, RelA);
    ecs_add_id(world, e1, Tag);
    ecs_entity_t e2 = ecs_new(world, RelA);
    ecs_entity_t e3 = ecs_new(world, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add(world, e1, RelB);
    ecs_add(world, e2, RelB);
    ecs_add(world, e3, RelB);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_2_any_src_w_pair() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);
    ECS_TAG(world, RelB);
    ECS_TAG(world, Tag);
    ECS_TAG(world, TgtA);

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(_, TgtA), RelB(_, TgtA)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_entity_t e1 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_add(world, e1, Tag);
    ecs_entity_t e2 = ecs_new_w_pair(world, RelA, TgtA);
    ecs_entity_t e3 = ecs_new_w_pair(world, RelA, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_add_pair(world, e1, RelB, TgtA);
    ecs_add_pair(world, e2, RelB, TgtA);
    ecs_add_pair(world, e3, RelB, TgtA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_rule_next(&it));
        test_uint(0, it.count);
        test_uint(ecs_pair(RelA, TgtA), ecs_field_id(&it, 1));
        test_bool(false, ecs_rule_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}

void RulesBasic_rule_w_iter_next() {
    ecs_world_t *world = ecs_init();

    ECS_TAG(world, RelA);

    ecs_entity_t ent = ecs_new_entity(world, "ent");

    ecs_rule_t *r = ecs_rule(world, {
        .expr = "RelA(ent)"
    });

    test_assert(r != NULL);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(false, ecs_iter_next(&it));
    }

    ecs_add(world, ent, RelA);

    {
        ecs_iter_t it = ecs_rule_iter(world, r);
        test_bool(true, ecs_iter_next(&it));
        test_uint(0, it.count);
        test_uint(RelA, ecs_field_id(&it, 1));
        test_uint(ent, ecs_field_src(&it, 1));
        test_bool(false, ecs_iter_next(&it));
    }

    ecs_rule_fini(r);

    ecs_fini(world);
}