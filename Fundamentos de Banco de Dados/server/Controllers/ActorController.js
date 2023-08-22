const Actor = require('../Models/actor.js');
const { Op } = require('sequelize');
const sequelize = require('../Models/db').sequelize;


function getPaginationParams(req) 
{
  const page = Number(req.query.page) || 1;
  let pageSize
  if (req.query.pageSize < 25) 
     pageSize = Number(req.query.pageSize) || 10;
  else 
     pageSize = 25;

  return {
    page,
    pageSize,
  };
}

async function paginate(model, page, pageSize, whereClause = {}) 
{
  const totalCount = await model.count({ where: whereClause });
  const totalPages = Math.ceil(totalCount / pageSize);

  if (page > totalPages) {
    page = totalPages;
  }

  const offset = (page - 1) * pageSize;
  const results = await model.findAll({
    where: whereClause,
    limit: pageSize,
    offset: offset,
  });

  return {
    results,
    totalPages,
    totalCount,
    currentPage: page,
  };
}


async function listarAtores(req, res) {
  try {
    const { page, pageSize } = getPaginationParams(req);
    const actors = await Actor.findAll({
      limit: pageSize,
      offset: (page - 1) * pageSize,
    });

    res.json(actors);
  }
  catch (error) {
    console.error(error);
    res.status(500).json({ error: 'Erro ao listar os atores' });
  }
}

async function actorsOrderName(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);


  const actors = await Actor.findAll({
    order:
      [
        ['actorName', req.query.order]
      ],
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(actors);
}

async function actorsOrderAge(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);


  const actors = await Actor.findAll({
    order:
      [
        ['dateOfBirth', 'ASC']
      ],
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(actors);
}
async function actorsOrderHeight(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);


  const actors = await Actor.findAll({
    order:
      [
        ['height', req.query.order]
      ],
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(actors);
}


async function heightActors(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);


  const actors = await Actor.findAll({
    where:
      {
          height: {
          [Op.between]: [req.query.height1, req.query.height2]
        }

      },
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(actors);
}
async function ethnicityActors(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);


  const actors = await Actor.findAll({
    where:
      {
        ethnicity: req.query.ethnicity

      },
    limit: pageSize,
    offset: (page - 1) * pageSize,
  });
  res.json(actors);
}

async function nameActor(req, res) 
{
      const { page, pageSize } = getPaginationParams(req);

      const totalCount = await Actor.count({
        where: {
          actorName: {
            [Op.like]: `%${req.query.actorName}%`
          }
        }
      });

      const totalPages = Math.ceil(totalCount / pageSize);

      let adjustedPage = page;
      if (page > totalPages)
        adjustedPage = totalPages;


      const actors = await Actor.findAll({
        where: {
          actorName: {
            [Op.like]: `%${req.query.actorName}%`
          }
        },
        limit: pageSize,
        offset: (adjustedPage - 1) * pageSize
      });

      res.json(actors);

}

async function countryActor(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const actors = await paginate(Actor, page, pageSize, { country: req.query.country });
  res.json(actors);
}

async function genderActor(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const actors = await paginate(Actor, page, pageSize, { actorSex: req.query.gender});

  res.json(actors.results);
}

async function moviesBiggersImbActors(req, res) {

  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query = `
              SELECT a.actorName, m.title AS movieName, m.IMDBRating
              FROM actor a
              JOIN cast c ON a.actorID = c.actorID
              JOIN movie m ON c.movieId = m.movieId
              WHERE (
                  SELECT COUNT(*)
                  FROM movie m2
                  WHERE m2.IMDBRating > m.IMDBRating
                      AND m2.movieId IN (
                          SELECT c2.movieId
                          FROM cast c2
                          WHERE c2.actorID = a.actorID
                      )
              ) < 5
              ORDER BY a.actorName, m.IMDBRating DESC
                  LIMIT ${pageSize}
                  OFFSET ${offset}
   `;

  const actors = await sequelize.query(query, { type: sequelize.QueryTypes.SELECT });

  res.json(actors);


}

async function actorCollaborationsWithDirectos(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query1 = `
    SELECT actorName, directorName, collaborations
    FROM (
      SELECT a.actorID, a.actorName AS actorName, d.directorId, d.directorName AS directorName,
             COUNT(*) AS collaborations,
             ROW_NUMBER() OVER (PARTITION BY a.actorID ORDER BY COUNT(*) DESC) AS collaboration_rank
      FROM actor a
      JOIN cast c ON a.actorID = c.actorID
      JOIN movie m ON c.movieId = m.movieId
      JOIN director d ON m.directorId = d.directorId
      GROUP BY a.actorID, d.directorId
    ) AS ranked_collab
    WHERE collaboration_rank <= 5
    ORDER BY actorName ASC, collaborations DESC
    LIMIT ${pageSize}
    OFFSET ${offset}
  `;
  const actors1 = await sequelize.query(query1, { type: sequelize.QueryTypes.SELECT });

  const query2 = `
    SELECT directorName, actorName, collaborations
    FROM (
      SELECT d.directorId, d.directorName AS directorName, a.actorId, a.actorName AS actorName,
             COUNT(*) AS collaborations,
             ROW_NUMBER() OVER (PARTITION BY d.directorId ORDER BY COUNT(*) DESC) AS collaboration_rank
      FROM director d
      JOIN movie m ON d.directorId = m.directorId
      JOIN cast c ON m.movieId = c.movieId
      JOIN actor a ON c.actorId = a.actorId
      GROUP BY d.directorId, a.actorId
    ) AS ranked_collab
    WHERE collaboration_rank <= 5
    ORDER BY directorId, collaborations DESC
    LIMIT ${pageSize}
    OFFSET ${offset}
  `;
  const actors2 = await sequelize.query(query2, { type: sequelize.QueryTypes.SELECT });

  const finalResult = [];

  for (let i = 0; i < actors1.length; i++) {
    const registerActor1 = actors1[i];
    const registerActor2 = actors2[i];

    const combinedObject = {
      directorName: registerActor1.directorName,
      actorName: registerActor1.actorName,
      collaborations: registerActor1.collaborations,
      actorName2: registerActor2.actorName,
      directorName2: registerActor2.directorName,
      collaborations2: registerActor2.collaborations
    };

    finalResult.push(combinedObject);
  }

  res.json(finalResult);
}

async function actorOrderMoviesWithDirectos(req, res) 
{
  const { page, pageSize } = getPaginationParams(req);
  const offset = (page - 1) * pageSize;

  const query1 = `
    SELECT actorName, directorName, collaborations
    FROM (
      SELECT a.actorID, a.actorName AS actorName, d.directorId, d.directorName AS directorName,
             COUNT(*) AS collaborations,
             ROW_NUMBER() OVER (PARTITION BY a.actorID ORDER BY COUNT(*) DESC) AS collaboration_rank
      FROM actor a
      JOIN cast c ON a.actorID = c.actorID
      JOIN movie m ON c.movieId = m.movieId
      JOIN director d ON m.directorId = d.directorId
      GROUP BY a.actorID, d.directorId
    ) AS ranked_collab
    WHERE collaboration_rank <= 5
    ORDER BY actorName ASC, collaborations DESC
    LIMIT ${pageSize}
    OFFSET ${offset}
  `;
  const actors1 = await sequelize.query(query1, { type: sequelize.QueryTypes.SELECT });

  const query2 = `
    SELECT directorName, actorName, collaborations
    FROM (
      SELECT d.directorId, d.directorName AS directorName, a.actorId, a.actorName AS actorName,
             COUNT(*) AS collaborations,
             ROW_NUMBER() OVER (PARTITION BY d.directorId ORDER BY COUNT(*) DESC) AS collaboration_rank
      FROM director d
      JOIN movie m ON d.directorId = m.directorId
      JOIN cast c ON m.movieId = c.movieId
      JOIN actor a ON c.actorId = a.actorId
      GROUP BY d.directorId, a.actorId
    ) AS ranked_collab
    WHERE collaboration_rank <= 5
    ORDER BY directorId, collaborations DESC
    LIMIT ${pageSize}
    OFFSET ${offset}
  `;
  const actors2 = await sequelize.query(query2, { type: sequelize.QueryTypes.SELECT });

  const finalResult = [];

  for (let i = 0; i < actors1.length; i++) {
    const registerActor1 = actors1[i];
    const registerActor2 = actors2[i];

    const combinedObject = {
      directorName: registerActor1.directorName,
      actorName: registerActor1.actorName,
      collaborations: registerActor1.collaborations,
      actorName2: registerActor2.actorName,
      directorName2: registerActor2.directorName,
      collaborations2: registerActor2.collaborations
    };

    finalResult.push(combinedObject);
  }

  res.json(finalResult);
}



module.exports = {
  listarAtores,
  nameActor,
  actorsOrderName,
  actorsOrderAge,
  actorsOrderHeight,
  countryActor,
  genderActor,
  moviesBiggersImbActors,
  actorCollaborationsWithDirectos,
  heightActors,
  ethnicityActors

};