<?php

class userStorage extends Storage
{
    public function __construct()
    {
        parent::__construct(new JsonIO('users.json'));
    }
}
