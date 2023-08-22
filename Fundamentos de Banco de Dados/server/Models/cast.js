const { DataTypes } = require('sequelize');
const db = require('./db');
const Movie = require('../Models/movie.js');
const Actor = require('./actor');



const Cast = db.sequelize.define('cast', {
    actorID: {
      type: DataTypes.INTEGER,
      allowNull: false,
      references: {
        model: 'actor',
        key: 'actorID'
      }
    },
    movieId: {
      type: DataTypes.INTEGER,
      allowNull: false,
      references: {
        model: 'movie',
        key: 'movieId'
      }
    }
  }, {
    sequelize: db.sequelize, 
    tableName: 'cast',
    timestamps: false,
    indexes: [
      {
        name: "actorID",
        using: "BTREE",
        fields: [
          { name: "actorID" },
        ]
      },
      {
        name: "movieId",
        using: "BTREE",
        fields: [
          { name: "movieId" },
        ]
      },
    ]
  });
  Cast.belongsTo(Actor,{
    constraint: true,
    foreignKey: "actorID"
  })
  module.exports = Cast;

